#include "glviewcontroller.hpp"
#include "glview.hpp"
#include <QKeyEvent>
#include "rectangle.hpp"
#include "controlgrid.hpp"
#define INITPOS 0.0f, 0.0f, -10.0f, 1.0f

GLViewController::GLViewController(GLView* view) : glview_(view), mode_(SELECT), draw_mode_(NONE), click_amount_(1), clamped_z_(0), current_selected_(nullptr) {
	this->click_color_ = { 1,0,0,1 };
	this->unclick_color_ = { 1,1,1,1 };
}

void GLViewController::setView(GLView* view) {
	this->glview_ = view;
}

void GLViewController::setDrawMode(DrawMode mode) {
	this->draw_mode_ = this->draw_mode_ ^ mode;
}

void GLViewController::setMode(Mode mode) {
	setCurrentUnclicked();
	if (mode == C0) {
		this->setClickAmount(2);
	}
	else if (mode == SELECT) {
		this->setClickAmount(1);
	}

	this->mode_ = mode;
}

void GLViewController::setClickAmount(int amount) {
	this->clicked_.clear();
	this->click_amount_ = amount;
}

void GLViewController::mousePressEvent(QMouseEvent* event) {
	switch (mode_) {
	case SELECT:
		pressSelectHandler(event);
		break;
	case C0:
		if (event->button() == Qt::RightButton) {
			pressC0Handler(event);
		}
		else {
			pressSelectHandler(event);
		}
		break;
	case DRAWCURVE:
		pressDrawCurveHandler(event);
		break;
	case DRAWCOONS:
		pressDrawCoonspatchHandler(event);
		break;
	case DRAWSURFACE:
		pressDrawSurfaceHandler(event);
		break;
	default:
		break;
	}
}

void GLViewController::mouseMoveEvent(QMouseEvent* event) const {
	switch (mode_) {
	case SELECT:
		moveSelectHandler(event);
		break;
	case C0:
		if (event->buttons() & Qt::RightButton) {
			moveC0Handler(event);
		}
		break;
	case DRAWCOONS:
	case DRAWSURFACE:
		moveDrawSurfaceHandler(event);
		break;
	default:
		break;
	}
}

void GLViewController::mouseReleaseEvent(QMouseEvent* event) {
	if (mode_ & (DRAWSURFACE | DRAWCOONS) && glview_->temp_model_) {
		setCurrentUnclicked();
		auto coords = glview_->temp_model_->getVertices();

		QMatrix4x4 mat;
		mat.setToIdentity();
		if (mode_ == DRAWSURFACE) {
			QVector4DMatrix surface = { { coords[0], coords[1] },{ coords[2], coords[3] } };
			std::shared_ptr<BezierSurface> ptr(new BezierSurface(mat, { INITPOS }, glview_->light));
			ptr->setCoordinates(surface);
			ptr->setDefaultShader(*glview_->prog_);
			if (glview_->phong_prog_) {
				ptr->setSurfaceShader(*glview_->phong_prog_);
			}
			ptr->addNormalShader(*glview_->normal_prog_);
			clearClicked();
			glview_->initModel(*ptr, nullptr);
			glview_->surfaces_.push_back(ptr);
			glview_->temp_model_.reset();
			//	glview_->current_surface_ = ptr.get();
		}
		else {
			QVector4DMatrix patch = { { coords[0]}, {coords[1] },  {coords[3]}, {coords[2]} };
			std::shared_ptr<CoonsPatch> ptr(new CoonsPatch(mat, { INITPOS }));
			ptr->setCoordinates(patch);
			ptr->setDefaultShader(*glview_->prog_);
			ptr->addNormalShader(*glview_->normal_prog_);
			clearClicked();
			glview_->initModel(*ptr, nullptr);
			glview_->patches_.push_back(ptr);
			glview_->temp_model_.reset();
			//	glview_->current_surface_ = ptr.get();
		}

	}
	else if (mode_ == C0 && event->button() == Qt::RightButton && current_selected_->type != COONS) {

		if (clicked_.isEmpty() || clicked_.size() <= 1) {
			return;
		}
		int row = current_selected_->row_index_;
		int col = current_selected_->col_index_;
		QVector4DMatrix mat = dynamic_cast<ControlGrid*>(current_selected_->clickable_)->getExtension();
		BezierSurface *surface;
		try {
			surface = dynamic_cast<BezierSurface*>(current_selected_->model_);
		}
		catch (std::bad_cast) {
			return;
		}
		if (row == -1) {
			if (col == 0) {
				surface->prependVCoordinates(mat);
			}
			else {
				surface->appendVCoordinates(mat);
			}
		}
		else if (col == -1) {
			if (row == 0) {
				surface->prependUCoordinates(mat);
			}
			else {
				surface->appendUCoordinates(mat);
			}
		}
		else if (row == 0 && col == 0) {
			surface->appendVCoordinates(mat);
		}
		glview_->makeCurrent();

		//dynamic_cast<BezierSurface*>(current_selected_->model_)->reinit(nullptr, true);
		clearClicked();
		glview_->temp_model_.reset();
		surface->reinit(nullptr, true);
	}
}

void GLViewController::pressSelectHandler(QMouseEvent* event) {
	QVector3D begin, end, direction;

	float radius = 0.2f;
	float radius2 = radius * radius;
	for (auto& current : glview_->surfaces_) {
		projectMouseEvent(event, current->getModelMatrix(), &begin, &end, &direction);
		if (checkClicked(*current, begin, direction, radius2)) {
			return;
		}
	}
	for(auto& current : glview_->patches_) {
		projectMouseEvent(event, current->getModelMatrix(), &begin, &end, &direction);
		if (checkClicked(*current, begin, direction, radius2)) {
			return;
		}
	}
}

void GLViewController::pressDrawCurveHandler(QMouseEvent* event) {
	QVector3D begin, end, direction;
	projectMouseEvent(event, &begin, &end, &direction);
	auto length = (clamped_z_ - begin.z()) / direction.z();
	QVector4D base = begin + length * direction;
	base.setW(1);
	QVector<QVector4D> vertical, coord = { {base} };
	if (!current_selected_ || current_selected_->clickable_ != nullptr) {
		ClickedModel clicked;
		clicked.clickable_ = nullptr;
		clicked.reference_ = nullptr;
		clicked.offset_ = { 0,0,0 };
		QMatrix4x4 mat;
		mat.setToIdentity();
		std::shared_ptr<BezierSurface> ptr(new BezierSurface(mat, { INITPOS }, glview_->light));
		ptr->appendVCoordinates(coord);
		ptr->setDefaultShader(*glview_->prog_);
		if (glview_->phong_prog_) {
			ptr->setSurfaceShader(*glview_->phong_prog_);
		}
		ptr->addNormalShader(*glview_->normal_prog_);
		clicked.model_ = ptr.get();
		addClicked(&clicked);
		glview_->surfaces_.push_back(ptr);
		glview_->initModel(*ptr.get(), nullptr);
		//glview_->current_surface_ = ptr.get();
	}
	else {
		try {
			dynamic_cast<BezierSurface*>(current_selected_->model_)->appendVCoordinates(coord);
			glview_->makeCurrent();
			dynamic_cast<BezierSurface*>(current_selected_->model_)->reinit(nullptr, true);
		}
		catch (std::bad_cast) {

		}

	}
}

void GLViewController::pressDrawSurfaceHandler(QMouseEvent* event) {
	QVector3D begin, end, direction;
	projectMouseEvent(event, &begin, &end, &direction);
	auto length = (clamped_z_ - begin.z()) / direction.z();
	auto base = begin + length * direction;
	std::make_shared<Rect::Rectangle>(QVector4D(base, 1), 0.1);
	glview_->temp_model_ = std::make_shared<Rect::Rectangle>(QVector4D(base, 1), 0.1);
	QVector4D initpos = { INITPOS };
	glview_->initModel(*glview_->temp_model_.get(), &initpos);

	ClickedModel clicked;
	clicked.clickable_ = static_cast<Rect::Rectangle*>(glview_->temp_model_.get());
	clicked.reference_ = &clicked.clickable_->getReference();
	clicked.model_ = glview_->temp_model_.get();
	clicked.offset_ = { 0,0,0 };
	this->addClicked(&clicked);

}

void GLViewController::pressDrawCoonspatchHandler(QMouseEvent* event) {
	pressDrawSurfaceHandler(event);
}

void GLViewController::pressC0Handler(QMouseEvent* event) {
	if (clicked_.isEmpty() || clicked_.size() <= 1 || current_selected_->type != SURFACE) {
		return;
	}
	int row = clicked_.front().row_index_;
	int col = clicked_.front().col_index_;
	for (int i = 1; i < clicked_.size(); i++) {
		row = clicked_[i].row_index_ == row ? row : -1;
		col = clicked_[i].col_index_ == col ? col : -1;
	}
	
	BezierSurface *surface;
	QVector4DMatrix mat;
	try {
		surface = dynamic_cast<BezierSurface*>(current_selected_->model_);
	}
	catch (std::bad_cast) {
		return;
	}

	if (row == -1) {
		if (col == 0) {
			mat = surface->c0PrependV();
		}
		else {
			mat = surface->c0AppendV();
		}
	}
	else if (col == -1) {
		if (row == 0) {
			mat = surface->c0PrependU();
		}
		else {
			mat = surface->c0AppendU();
		}
	}
	else if (row == 0 && col == 0) {
		mat = surface->c0AppendV();
	}
	else {
		return;
	}

	QVector3D begin, end, direction;
	projectMouseEvent(event, &begin, &end, &direction);
	auto length = (clamped_z_ - begin.z()) / direction.z();
	auto base = begin + length * direction;
	glview_->temp_model_ = std::make_shared<ControlGrid>(QVector4D(base, 1), mat);
	QVector4D initpos = { INITPOS };
	glview_->initModel(*glview_->temp_model_.get(), &initpos);
	glview_->temp_model_->setModelMatrix(surface->getModelMatrix());

	ClickedModel clicked;
	clicked.clickable_ = static_cast<ControlGrid*>(glview_->temp_model_.get());
	clicked.reference_ = &clicked.clickable_->getReference();
	clicked.model_ = current_selected_->model_;
	clicked.offset_ = { 0,0,0 };
	clicked.row_index_ = row;
	clicked.col_index_ = col;
	this->addClicked(&clicked);
}

void GLViewController::moveSelectHandler(QMouseEvent* event) const {
	if (current_selected_ == nullptr) {
		return;
	}
	QVector3D begin, end, direction;
	projectMouseEvent(event, current_selected_->model_->getModelMatrix(), &begin, &end, &direction);
	auto length = current_selected_->offset_.length();
	float w = current_selected_->reference_->w();
	*current_selected_->reference_ = (begin + length * direction);
	current_selected_->reference_->setW(1);
	*current_selected_->reference_ *= w;
	glview_->makeCurrent();
	emit glview_->clickedVertex(current_selected_->reference_);
	current_selected_->model_->reinit();
}

void GLViewController::moveC0Handler(QMouseEvent* event) const {
	if (!current_selected_ || !glview_->temp_model_) {
		return;
	}
	QVector3D begin, end, direction;
	projectMouseEvent(event, &begin, &end, &direction);
	auto length = (clamped_z_ - begin.z()) / direction.z();
	*current_selected_->reference_ = (begin + length * direction);
	current_selected_->reference_->setW(1);
	glview_->makeCurrent();
	glview_->temp_model_->reinit();

}

void GLViewController::moveDrawSurfaceHandler(QMouseEvent* event) const {
	if (current_selected_ == nullptr) {
		return;
	}
	QVector3D begin, end, direction;
	projectMouseEvent(event, &begin, &end, &direction);
	auto length = (clamped_z_ - begin.z()) / direction.z();
	*current_selected_->reference_ = (begin + length * direction);
	current_selected_->reference_->setW(1);
	glview_->makeCurrent();
	current_selected_->model_->reinit();
}

void GLViewController::addClicked(ClickedModel* clicked) {
	if (clicked == nullptr) {
		return;
	}
	clicked_.push_back(*clicked);
	this->current_selected_ = &clicked_[clicked_.size() - 1];
	while (clicked_.size() > click_amount_) {
		if (clicked_.front().clickable_ != nullptr) {
			clicked_.front().clickable_->setUnclicked();
		}
		clicked_.pop_front();
	}
}

void GLViewController::setCurrentUnclicked() {
	if (current_selected_ != nullptr) {
		if (current_selected_->clickable_) {
			current_selected_->clickable_->setUnclicked(unclick_color_);
		}
		current_selected_ = nullptr;
	}
}

void GLViewController::clearClicked() {
	setCurrentUnclicked();
	for (auto& clicked : clicked_) {
		if (clicked.clickable_) {
			clicked.clickable_->setUnclicked();
		}
	}
	this->clicked_.clear();
}

void GLViewController::setClampedZ(float f) {
	this->clamped_z_ = f;
}

BezierSurface* GLViewController::getSelectedSurface() {
	if (!current_selected_ || current_selected_->type != SURFACE) {
		return nullptr;
	}
	return static_cast<BezierSurface*>(current_selected_->model_);
}

CoonsPatch* GLViewController::getSelectedCoonsPatch() {
	if (!current_selected_ || current_selected_->type != COONS) {
		return nullptr;
	}
	return static_cast<CoonsPatch*>(current_selected_->model_);
}

bool GLViewController::checkClicked(BezierSurface& surface, const QVector3D& begin, const QVector3D& direction, const float radius) {
	QVector4D * prev_selected = nullptr;
	if (current_selected_) {
		prev_selected = current_selected_->reference_;
	}
	auto u = 0;
	auto v = 0;
	if (mode_ != C0) {
		setCurrentUnclicked();
	}
	else {
		u = surface.getUSize();
		v = surface.getVSize();
	}
	for (auto i = 0; i < surface.size(); i++) {
		if (mode_ == C0) {
			auto border_test = i % v;
			if (!(i < u || i + u >= (u*v)) && (border_test != 0 && border_test != u - 1)) {
				continue;
			}

		}
		QVector4D& coord = surface.get(i);
		QVector3D L = (coord.toVector3DAffine() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius) {
			continue;
		}
		ClickedModel clicked(surface, i);
		clicked.offset_ = coord.toVector3DAffine() - begin;
		addClicked(&clicked);
		this->current_selected_->clickable_->setClicked(click_color_);
		emit glview_->clickedVertex(clicked.reference_);
		//glview_->current_surface_ = &surface;
		if (prev_selected == clicked.reference_) {
			continue;
		}
		emit glview_->clickedSurface(&surface);
		return true;
	}
	return false;
}

bool GLViewController::checkClicked(CoonsPatch& patch, const QVector3D& begin, const QVector3D& direction, const float radius) {
	QVector4D * prev_selected = nullptr;
	if (current_selected_) {
		prev_selected = current_selected_->reference_;
	}
	for (auto i = 0; i < patch.size(); i++) {
		QVector4D& coord = patch.get(i);
		QVector3D L = (coord.toVector3DAffine() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius) {
			continue;
		}
		ClickedModel clicked(patch, i);
		clicked.offset_ = coord.toVector3DAffine() - begin;
		addClicked(&clicked);
		this->current_selected_->clickable_->setClicked(click_color_);
		emit glview_->clickedVertex(clicked.reference_);
		//glview_->current_surface_ = &surface;
		if (prev_selected == clicked.reference_) {
			continue;
		}
		return true;
	}
	return false;
}

void GLViewController::projectMouseEvent(QMouseEvent* event, QVector3D* begin, QVector3D* end, QVector3D* direction) const {
	if (!begin || !end || !direction) {
		return;
	}
	QMatrix4x4 mat;
	mat.setColumn(3, { INITPOS });
	projectMouseEvent(event, mat, begin, end, direction);
}

void GLViewController::projectMouseEvent(QMouseEvent* event, const QMatrix4x4 model, QVector3D* begin, QVector3D* end, QVector3D* direction) const {
	if (!begin || !end || !direction) {
		return;
	}
	QVector2D pos(event->pos());
	QRect viewp(0, 0, glview_->width(), glview_->height());
	*begin = QVector3D(pos, -10.0f).unproject(this->glview_->view_ * model, glview_->projection_, viewp);
	*end = QVector3D(pos.x(), glview_->height() - pos.y(), 1.0f).unproject(this->glview_->view_ * model, glview_->projection_, viewp);
	*direction = (*end - *begin).normalized();
}

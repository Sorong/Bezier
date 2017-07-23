#include "coonspatch.hpp"
#include "coonscalculator.hpp"


#define VERTEXPOINTSCALE 0.2f
#define DEGREEELEVATIONS 3

CoonsPatch::CoonsPatch(QMatrix4x4& model, const QVector4D& pos)
	: Model(model, pos),
	  patch(new Patch(model, pos)) {
}

CoonsPatch::~CoonsPatch()
{
	delete patch;
}

void CoonsPatch::init(QVector4D* position) {
	if (!default_shader_ || coordinates_.isEmpty()) {
		return;
	}
	for(int i = 0; i < DEGREEELEVATIONS; i++) {
		degreeElevation();
	}
	
	createSubModels();
	patch->setCoordinates(this->patch_);
	patch->setDefaultShader(*default_shader_);
	patch->init(position);
	Model::initBuffer();
	if (position) {
		this->setPosition(*position);
	}
}

void CoonsPatch::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	default_shader_->bind();
	default_shader_->setUniformValue("mvp", mvp);
	glBindVertexArray(this->vertexarrayobject_);
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
	for (auto& ico : base_points_) {
		ico->setModelMatrix(this->model_);
		ico->translateToReference();
		ico->scale(VERTEXPOINTSCALE);
		ico->render(projection, view);
	}
	for(auto& curve : curves_) {
		curve->setModelMatrix(this->model_);
		curve->render(projection, view);
	}
	patch->setModelMatrix(this->model_);
	patch->render(projection, view);
}

void CoonsPatch::reinit(QVector4D* pos) {
	int ico = 0;
	this->vertices_.clear();
	for (auto i = 0; i < coordinates_.size(); i++) {
		auto j = 0;
		for (j = 0; j < coordinates_[i].size(); j++) {
			this->coordinates_[i][j] = base_points_[ico]->getReference();
			this->vertices_.push_back(this->coordinates_[i][j]);
			base_points_[ico]->reinit(pos);
			ico++;
		}
		this->vertices_.push_back(this->coordinates_[i][j - 1]);
	}
	this->vertices_.push_back(this->coordinates_[0][0]);
	this->createCurves();
	this->createPatch();
	patch->setCoordinates(this->patch_);
	patch->reinit();
	for (auto& curve : curves_) {
		curve->setDefaultShader(*default_shader_);
		curve->init();
	} 
	Model::reinit(pos);
}

void CoonsPatch::setCoordinates(QVector4DMatrix& coordinates) {
	this->coordinates_ = coordinates;
}

void CoonsPatch::degreeElevation() {
	QVector4DMatrix coordinates;
	QVector<QVector4D> side;
	for (auto i = 0; i < coordinates_.size(); i++) {
		auto j = 0;
		side.clear();
		for (j = 0; j < coordinates_[i].size(); j++) {
			side.push_back(this->coordinates_[i][j]);
		}
		side.push_back(this->coordinates_[(i + 1) % this->coordinates_.size()][0]);
		coordinates.push_back(side);
	}
	BezierCalculator calc;
	for(auto& current : coordinates) {
		calc.degreeElevation(current);
	}
	int i = 0;
	for(; i < coordinates.size(); i++) {
		coordinates[i].removeLast();
	}
	coordinates_ = coordinates;

}

Clickable& CoonsPatch::getClicked(int index) {
	return *this->base_points_[index];
}

QVector4D& CoonsPatch::get(int index) const {
	return this->base_points_.at(index)->getReference();
}

int CoonsPatch::size() const {
	return this->base_points_.size();
}

void CoonsPatch::createSubModels() {
	createBasePoints();
	createCurves();
	createPatch();
	for(auto& ico : base_points_) {
		ico->setDefaultShader(*default_shader_);
		ico->init();
	}
	for(auto& curve : curves_) {
		curve->setDefaultShader(*default_shader_);
		curve->init();
	}
}

void CoonsPatch::createBasePoints() {
	for(auto i = 0; i < coordinates_.size(); i++) {
		auto j = 0;
		for(j = 0; j < coordinates_[i].size(); j++) {
			this->vertices_.push_back(this->coordinates_[i][j]);
			std::shared_ptr<Icosahedron> icosahedron = std::make_shared<Icosahedron>(model_, this->coordinates_[i][j]);
			icosahedron->setColor({ 1,1,1,1 });
			this->base_points_.push_back(icosahedron);

		}
		this->vertices_.push_back(this->coordinates_[i][j-1]);
	}
	this->vertices_.push_back(this->coordinates_[0][0]);
	for(int i = 0; i < vertices_.size() - 1; i++) {
		indices_.push_back(i);
		indices_.push_back(i + 1);
	}
	this->colors_.fill({ 0,1,0,1 }, this->vertices_.size());
}

void CoonsPatch::createCurves() {
	this->curves_.clear();
	QVector<QVector4D> side;
	BezierCalculator calc;
	for (auto i = 0; i < coordinates_.size(); i++) {
		auto j = 0;
		QVector<QVector4D> curve;
		side.clear();
		for (j = 0; j < coordinates_[i].size(); j++) {
				side.push_back(this->coordinates_[i][j]);
		}
		side.push_back(this->coordinates_[(i + 1) % this->coordinates_.size()][0]);
		
		
		calc.bezierCurve(side, curve, 0.05);
		std::shared_ptr<BezierCurve> curr_curve = std::make_shared<BezierCurve>(model_, pos_);
		if(i > 1 ) {
			QVector<QVector4D> curve_reverse;
			for(int k = curve.size() - 1; k >= 0; k--) {
				curve_reverse.push_back(curve[k]);
			}
			curr_curve->setBaseCoordinates(curve_reverse);
		} else {
			curr_curve->setBaseCoordinates(curve);
		}
		curr_curve->setColor({ 1,0,0,1 });
		curves_.push_back(curr_curve);
	}
}

void CoonsPatch::createPatch() {
	QVector4DMatrix ltrb = { curves_[0]->getVertices(), curves_[1]->getVertices(), curves_[2]->getVertices(), curves_[3]->getVertices() };
	CoonsCalculator calc;
	this->patch_.clear();
	calc.getCoonsPatch(ltrb, &patch_, 0.05,0.05);
}

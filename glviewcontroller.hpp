#pragma once


class GLView;

class GLViewController {
public:
	GLViewController(GLView* view);
	void setView(GLView* view);
private:
	GLView* view_;
};

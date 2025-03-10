#include <QApplication>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget: public QOpenGLWidget, protected QOpenGLFunctions {
protected:
	void initializeGL() override {
		initializeOpenGLFunctions();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	}

	void paintGL() override {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void resizeGL(int w, int h) override {
		glViewport(0, 0, w, h);
	}
};

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	OpenGLWidget widget;

	widget.resize(800, 600);
	widget.show();

	return app.exec();
}

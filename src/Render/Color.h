#ifndef COLOR_H
#define COLOR_H
#include <algorithm>

class Color {
public:
	Color();
	Color(int rW, int gW, int bW, int aW);
	Color(double rW, double gW, double bW, double aW);

	static Color white();
	static Color black();
	static Color red();
	static Color green();
	static Color blue();

	int r() const;
	int g() const;
	int b() const;
	int a() const;

	void setRed(int rW);
	void setGreen(int gW);
	void setBlue(int bW);
	void setAlpha(int aW);
	void setRed(double rW);
	void setGreen(double gW);
	void setBlue(double bW);
	void setAlpha(double aW);
	void setAll(int rW, int gW, int bW, int aW);

	Color operator* (double x) const;
	Color operator+ (Color c) const;
	Color operator- (Color c) const;
	void normalize();

private:
	int redW;
	int greenW;
	int blueW;
	int alphaW;
};

#endif //COLOR_H
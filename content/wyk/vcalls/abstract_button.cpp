#include <string>
#include <iostream>

class BaseButton {
    double _x = 0, _y = 0;
    double _w = 100, _h = 50;
    std::string _text;
   protected:
    void (*_on_click)() = nullptr;

   public:
    BaseButton() = default;
    std::pair<double, double> position() const { return {_x, _y}; }
    void setPosition(double x, double y) { _x = x; _y = y; }
    std::pair<double, double> size() const { return {_w, _h}; }
    void setSize(double w, double h) { _w = w; _h = h; }
    const std::string& text() const { return _text; }
    void setText(const std::string& text) { _text = text; }
    void setOnClick(void (*fn)()) { _on_click = fn; }
};

class Button : public BaseButton {
  public:
    void click() {
        _on_click();
    }
    void draw();
};

class ToggleButton : public BaseButton {
    bool _toggled = false;

   public:
    void click() {
        _toggled = !_toggled;
        _on_click();
    }
    bool toggled() const { return _toggled; }
    void draw();
};

class RoundButton : public BaseButton  {
   public:
    void click() {
        _on_click();
    }
    void draw(); // draws rounded edges
};


void do_click() {
    std::cout << "click" << std::endl;
}

int main() {
     Button b;
     b.setText("Button");
     b.setPosition(0, 0);
     b.setOnClick(do_click);
     ToggleButton tb;
     tb.setText("Toggle");
     tb.setPosition(100, 0);
     tb.setOnClick(do_click);
     RoundButton rb;
     rb.setText("Round");
     rb.setPosition(200, 0);
     rb.setOnClick(do_click);

     b.click();
     tb.click();
     rb.click();

     return 0;
}
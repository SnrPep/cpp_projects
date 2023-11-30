#include <FL/Fl.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Box.H>
#include <Fl/fl_draw.H>
#include <stdio.h>
#include <map>
#include <math.h>

#define CANVAS_X 10
#define CANVAS_Y 10
#define CANVAS_WIDTH 180
#define CANVAS_HEIGHT 100
#define GRID_LEN 5 // размер зерна в холсте

Fl_Box *count_label;
char buf[16];

struct point {
    int x, y;
};

typedef std::map<std::pair<int, int>, point> PointMap; // карта с координатами пикселей
PointMap pixels;


class PaintWindow : public Fl_Window { //немного модифицируем стандартное окно

public:

    PaintWindow(int w, int h, char const *title) : Fl_Window(w, h, title) {

    }

    void setpixel(int x, int y, bool add) {
        std::pair<int, int> p = std::make_pair(x * GRID_LEN, y * GRID_LEN); // с помощью древней магии мы используем два аргумента как ключ к карте пикселей

        if (add) {
            point pixel;
            pixel.x = x * GRID_LEN;
            pixel.y = y * GRID_LEN;
            pixels[p] = pixel;
        } else {
            pixels.erase(p);
        }

        sprintf(buf, "%d px", pixels.size());
        count_label->label(buf); // обновляем надпись

        redraw();
    }

    int handle(int event) {
        double x = Fl::event_x();
        double y = Fl::event_y();

        if (x < CANVAS_X || x > CANVAS_X + CANVAS_WIDTH - 1 || y < CANVAS_Y || y > CANVAS_Y + CANVAS_HEIGHT - 1) // если мышка за границей холста, то ничего не делаем
            return Fl_Window::handle(event);

        if (event == FL_PUSH) {
            setpixel(round(x / GRID_LEN), round(y / GRID_LEN), Fl::event_button() == FL_LEFT_MOUSE); //округляем координаты исходя из зерна, добавляем или удаляем пиксель в зависимости от кнопки мыши
        }
        if (event == FL_DRAG) {
            setpixel(round(x / GRID_LEN), round(y / GRID_LEN), Fl::event_button() == FL_LEFT_MOUSE);
        }

        return Fl_Window::handle(event);
    }

    void draw(void) {
        Fl_Window::draw();
        fl_color(FL_WHITE);
        fl_rectf(CANVAS_X, CANVAS_Y, CANVAS_WIDTH, CANVAS_HEIGHT); // заливаем белый квадрат
        fl_color(FL_BLACK);

        typedef PointMap::iterator it_type;
        for (it_type iterator = pixels.begin(); iterator != pixels.end(); iterator++) { // перебираем все пиксели
            int x = iterator->second.x;
            int y = iterator->second.y;
            fl_rectf(x, y, 5, 5); // рисуем точки
        }
    }
};

PaintWindow *window;

int main(void) {
    window = new PaintWindow(200, 300, "Points"); //создаём окно
    count_label = new Fl_Box(34, 177, 133, 56, "..."); // создаём подпись
    count_label->labelsize(50); //выставляем размер шрифта

    window->end();  // закрываем группу окна
    window->show(); // показываем окно
    return Fl::run();
}

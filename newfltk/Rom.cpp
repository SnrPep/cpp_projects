#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <cmath>
#include <stdio.h>
#include <algorithm>

int N,n,R,color;
Fl_Input *vn, *vN,*vR;
Fl_Input *vr;
Fl_Button *goButton;
Fl_Button *error, *colorButton;
Fl_Button *btn[640000];

static void cb_goButton(Fl_Button*, void*);

void cb_vN(Fl_Button *w, void *data) {
    sscanf(vN->value(), "%d", &N);

}

void cb_vn(Fl_Button *w, void *data) {
    sscanf(vn->value(), "%d", &n);
}

void cb_vR(Fl_Button *w, void *data) {
    sscanf(vR->value(), "%d", &R);
    char r[100];
    sprintf(r,"%ld",R/4);
    vr->value(r);
}

void cb_btn(Fl_Button *w, void *data) {
}

void cb_colorButton(Fl_Button *w, void *data) {
    color++;
    color%=3;
    switch (color) {
        case 0:
            colorButton->color(FL_RED);
            break;
        case 1:
            colorButton->color(FL_BLUE);
            break;
        case 2:
            colorButton->color(FL_GREEN);
            break;
    }
}


static void cb_goButton(Fl_Button*, void*data) {
    int i,w,h,ix ,iy/*, n =7*/;
    double rho, j,x, y, fi, /*R=350,*/ r=R/4;
    if ((N>800) || (N<30) ||(R < 30)||(R>350)||(n < 3)||(n>20)){
        Fl_Window *win = new Fl_Window(200, 200);
        error = new Fl_Button(0, 0, 200, 200, "Error");
        error->box(FL_FLAT_BOX);
        error->color(FL_BACKGROUND_COLOR);
        error->down_box(FL_NO_BOX);
        win->show();
        win->end();
    }
    else{
        Fl_Window *win = new Fl_Window(N, N);
        for(j=0;j<1;j+=0.01){
            for (fi = 0; fi < 2*M_PI; fi+=0.01) {
                rho = (R * fabs(sin((double)n/2*fi)))*j;
                x = rho * cos(fi);
                y = rho * sin(fi);
                ix = x+N/2;
                iy = y+N/2;
                btn[i]=new Fl_Button(ix,iy,3,3," ");
                btn[i]->callback((Fl_Callback *)cb_btn);
                btn[i]->box(FL_FLAT_BOX);
                switch (color) {
                    case 0:
                        btn[i]->color(FL_RED);
                        break;
                    case 1:
                        btn[i]->color(FL_BLUE);
                        break;
                    case 2:
                        btn[i]->color(FL_GREEN);
                        break;
                }
                btn[i]->down_box(FL_NO_BOX);
                i++;
            }
        }

        for (fi = 0; fi < 2*M_PI; fi+=0.01) {
            for(rho=0; rho<r;rho+=2){
                x = rho * cos(fi);
                y = rho * sin(fi);
                ix = x+N/2;
                iy = y+N/2;
                btn[i]=new Fl_Button(ix,iy,3,3," ");
                btn[i]->callback((Fl_Callback *)cb_btn);
                btn[i]->box(FL_FLAT_BOX);
                btn[i]->color(FL_YELLOW);
                btn[i]->down_box(FL_NO_BOX);
                i++;
            }
        }
        win->show();
        win->end();
    }

};

int main(int argc, char **argv) {
    Fl_Double_Window *window = new Fl_Double_Window(405, 200);

    vN = new Fl_Input(40, 32, 80, 50, "N");
    vN->callback((Fl_Callback *)cb_vN);
    vN->when(FL_WHEN_CHANGED);

    vn = new Fl_Input(40, 105, 80, 50, "n");
    vn->callback((Fl_Callback *)cb_vn);
    vn->when(FL_WHEN_CHANGED);

    vR = new Fl_Input(145, 32, 80, 50, "R");
    vR->callback((Fl_Callback *)cb_vR);
    vR->when(FL_WHEN_CHANGED);

    vr = new Fl_Input(145, 105, 80, 50, "r");

    colorButton = new Fl_Button(255, 32, 110, 50, "Color");
    colorButton->color(FL_RED);
    colorButton->callback((Fl_Callback*)cb_colorButton);

    goButton = new Fl_Button(255, 105, 110, 50, "GO");
    goButton->callback((Fl_Callback*)cb_goButton);

    window->end();
    window->show(argc, argv);
    return Fl::run();
}

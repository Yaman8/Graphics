#pragma once

#include"lineFunc.h"
#include"matrix.h"
#include"colorOptions.h"
void wireFrame(vect4 v1, vect4 v2, vect4 v3, const vec3& color);
void fillTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color);

void fillBottomFlatTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color);
void fillTopFlatTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color);

void drawWireframe_model(std::vector<Triangle>& model);
void draw_model(std::vector<Triangle>& model);


std::vector<float> interpolate(float i0, float d0, float il, float dl)
{
    std::vector<float> values;

    if (i0 == il)
    {
        values.push_back(d0);
        return values;
    }

    float a = (dl - d0) / (il - i0);
    float d = d0;

    for (int i = i0; i < il; i++)
    {
        values.push_back(d);
        d = d + a;
    }
    return values;
}


void wireFrame(vect4 v1, vect4 v2, vect4 v3, const vec3& color) {
    //fillTriangle(v1, v2, v3, color);
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v1.x, v1.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v2.x, v2.y, color);
}

void fillTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color) {
    if (v1.y > v2.y) { std::swap(v2, v1); }
    if (v1.y > v3.y) { std::swap(v3, v1); }
    if (v2.y > v3.y) { std::swap(v3, v2); }

    if (int(v2.y) == int(v3.y)) { fillBottomFlatTriangle(v1, v2, v3, color); }
    else if (int(v1.y) == int(v2.y)) { fillTopFlatTriangle(v1, v2, v3, color); }
    else
    {
        // general case - split the triangle in a topflat and bottom-flat one
        vect4* v4 = new vect4({
            (v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)),v2.y, 0
            });
        fillBottomFlatTriangle(v1, v2, *v4, color);
        fillTopFlatTriangle(v2, *v4, v3, color);
    }
}

void fillBottomFlatTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    // cout <<"a"<< (v2.x - v1.x) / (v2.y - v1.y)<<endl;
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v1.x, v1.y, color);

    for (int scanlineY = v1.y; scanlineY < v2.y - 0.5f; scanlineY++)
    {
        // if (scanlineY == v2.y)
        // {
        //     std::cout << "x" << curx1 << "," << curx2 << std::endl;
        //     std::cout << v2.y << endl;
        // }
        Line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fillTopFlatTriangle(vect4 v1, vect4 v2, vect4 v3, const vec3& color)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v1.x, v1.y, color);

    for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
    {
        Line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void drawWireframe_model(std::vector<Triangle>& model)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            wireFrame(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);
            //std::cout << model[i].vertices[0] << " ";
        }
        //std::cout << std::endl;
    }
}

void draw_model(std::vector<Triangle>& model)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fillTriangle(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2],model[i].color);
            //model[i].gouraudRasterize1();
        }
        //Point n = (wmodel[i].vertices[2] - wmodel[i].vertices[0]).crossProduct(wmodel[i].vertices[1] - wmodel[i].vertices[0]);
        //n.normalize();
        //float intensity = dotProduct(n, lightDir);
        //std::cout<<intensity<<std::endl;
        //vec3 col;
        //if (intensity > 0)
        
    }
}

void Triangle::setIntensity(std::vector<float> intense)
{
    vertex_intensity[0] = { vertices[0].x, vertices[0].y, vertices[0].z, intense[0] };
    vertex_intensity[1] = { vertices[1].x, vertices[1].y, vertices[1].z, intense[1] };
    vertex_intensity[2] = { vertices[2].x, vertices[2].y, vertices[2].z, intense[2] };
    // isGouraudShading = true;
}

void Triangle::gouraudRasterize1()
{
    // Sort the points so that y0 <= yl <= y2
    auto P0 = vertex_intensity[0];
    auto P1 = vertex_intensity[1];
    auto P2 = vertex_intensity[2];

    if (P1.y < P0.y)
    {
        std::swap(P1, P0);
    }
    if (P2.y < P0.y)
    {
        std::swap(P2, P0);
    }
    if (P2.y < P1.y)
    {
        std::swap(P2, P1);
    }

    //  Compute the x coordinates of the triangle edges
    std::vector<float> x01 = interpolate(P0.y, P0.x, P1.y, P1.x);
    std::vector<float> h01 = interpolate(P0.y, P0.w, P1.y, P1.w);

    std::vector<float> x12 = interpolate(P1.y, P1.x, P2.y, P2.x);
    std::vector<float> h12 = interpolate(P1.y, P1.w, P2.y, P2.w);

    std::vector<float> x02 = interpolate(P0.y, P0.x, P2.y, P2.x);
    std::vector<float> h02 = interpolate(P0.y, P0.w, P2.y, P2.w);

    //  Concatenate the short sides
    x01.pop_back();
    std::vector<float> x012;
    x012.resize(x01.size() + x12.size());
    std::copy(x01.begin(), x01.end(), x012.begin());
    std::copy(x12.begin(), x12.end(), x012.begin() + x01.size());

    // std::cout<<"------------------------------------------------\n";
    h01.pop_back();

    std::vector<float> h012;
    h012.resize(h01.size() + h12.size());
    std::copy(h01.begin(), h01.end(), h012.begin());
    std::copy(h12.begin(), h12.end(), h012.begin() + h01.size());

    //  Determine which is left and which is right
    int m = x012[x012.size() / 2];
    std::vector<float> x_left, x_right, h_left, h_right;

    if (x02[m] < x012[m])
    {
        x_left = x02;
        h_left = h02;

        x_right = x012;
        h_right = h012;
    }
    else
    {
        x_left = x012;
        h_left = h012;

        x_right = x02;
        h_right = h02;
    }
    // printVec(x_left);
    // std::cout<<"------------------------------------------------\n";
    // printVec(x_right);

    // Draw the horizontal segments
    for (float y = P0.y; y < P2.y - 1; y++)
    {
        auto x_l = x_left[y - P0.y];
        auto x_r = x_right[y - P0.y];

        auto h_segment = interpolate(x_l, h_left[y - P0.y], x_r, h_right[y - P0.y]);

        for (float x = x_l; x < x_r; x++)
        {
            vec3 shadedColor = color * h_segment[x - x_l];
            // maths::printvec(shadedColor);
            putpixel(x, y, shadedColor);
        }
    }
}



void Triangle::gouraudRasterize2()
{

    auto a = vertex_intensity[0];
    auto b = vertex_intensity[1];
    auto c = vertex_intensity[2];
    // vertex arr[3] = { A,B,C };
    if (a.x > b.y)
    {
        std::swap(b, a);
    }
    if (a.x > c.y)
    {
        std::swap(c, a);
    }
    if (b.y > c.y)
    {
        std::swap(c, b);
    }

    float dx1, di1, dr1, dg1, db1, ddp1, ddp2, ddp3, dx2, dr2, dg2, db2, dx3, dr3, dg3, db3, dr, dg, db, ddp;
    if (b.y - a.y > 0)
    {
        dx1 = (b.x - a.x) / (b.y - a.y);
        ddp1 = (b.w - a.w) / (b.y - a.y);
    }
    else
        dx1 = dr1 = dg1 = db1 = 0, ddp1 = 0;
    ;

    if (c.y - a.y > 0)
    {
        dx2 = (c.x - a.x) / (c.y - a.y);
        ddp2 = (c.w - a.w) / (c.y - a.y);
    }
    else
        dx2 = dr2 = dg2 = db2 = ddp2 = 0;

    if (c.y - b.y > 0)
    {
        dx3 = (c.x - c.x) / (c.y - b.y);
        ddp3 = (c.w - b.w) / (c.y - b.y);
    }
    else
        dx3 = dr3 = dg3 = db3 = ddp3 = 0;
    vect4 S, E, P;
    S = a;
    E = a;
    if (dx1 > dx2)
    {
        for (; S.y <= b.y; S.y++, E.y++)
        {
            if (E.x - S.x > 0)
            {
                ddp = (E.w - S.w) / (E.x - S.x);
            }
            else
                dr = dg = db = ddp = 0;
            P = S;
            for (; P.x < E.x; P.x++)
            {
                //MULTIPLY
                vec3 ncolor = color * P.w;
                putpixel(P.x, P.y, ncolor);
                P.w += ddp;
            }
            //MULTIPLY ??
            S.x += dx2;
            S.w += ddp2;
            E.x += dx1;
            E.w += ddp1;
        }

        E = b;
        for (; S.y <= c.y; S.y++, E.y++)
        {
            if (E.x - S.x > 0)
            {
                //MULTIPLY
                vec3 ncolor = color * P.w;
                ddp = (E.w - S.w) / (E.x - S.x);
            }
            else
                dr = dg = db = 0;
            P = S;
            for (; P.x <= E.x; P.x++)
            {
                //multiply
                vec3 ncolor = color * P.w;
                putpixel(P.x, P.y, ncolor);
                P.w += ddp;
            }
            S.x += dx2;
            S.w += ddp2;
            E.x += dx3;
            E.w += ddp3;
        }
    }
    else
    {
        for (; S.y <= b.y; S.y++, E.y++)
        {
            if (E.x - S.x > 0)
            {
                //MULTIPLY
                vec3 ncolor = color * P.w;
                ddp = (E.w - S.w) / (E.x - S.x);
            }
            else
                dr = dg = db = ddp = 0;

            P = S;
            for (; P.x < E.x; P.x++)
            {
                vec3 ncolor = color * P.w;
                //multiply
                putpixel(P.x, P.y, ncolor); //doubtful-----------------------------------------------------------------------
                P.w += ddp;
            }
            S.x += dx1;
            S.w += ddp1;
            E.x += dx2;
            E.w += ddp2;
        }

        S = b;
        for (; S.y <= c.y; S.y++, E.y++)
        {
            if (E.x - S.x > 0)
            {
                //MULTIPLY
                ddp = (E.w - S.w) / (E.x - S.x);
            }
            else
                dr = dg = db = ddp = 0;

            P = S;
            for (; P.x < E.x; P.x++)
            {
                vec3 ncolor = color * P.w;
                putpixel(P.x, P.y, ncolor);
                //MULTIPLY
                P.w += ddp;
            }
            S.x += dx3;
            S.w += ddp3;
            E.x += dx2;
            E.w += ddp2;
        }
    }
}
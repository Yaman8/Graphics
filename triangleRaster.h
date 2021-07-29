#pragma once

void wireFrame(Point v1, Point v2, Point v3, const vec3& color);
void fillTriangle(Point v1, Point v2, Point v3, const vec3& color);

void fillBottomFlatTriangle(Point v1, Point v2, Point v3, const vec3& color);
void fillTopFlatTriangle(Point v1, Point v2, Point v3, const vec3& color);

void wireFrame(Point v1, Point v2, Point v3, const vec3& color) {
    //fillTriangle(v1, v2, v3, color);
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v1.x, v1.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v2.x, v2.y, color);
}

void fillTriangle(Point v1, Point v2, Point v3, const vec3& color) {
    if (v1.y > v2.y) { std::swap(v2, v1); }
    if (v1.y > v3.y) { std::swap(v3, v1); }
    if (v2.y > v3.y) { std::swap(v3, v2); }

    if (int(v2.y) == int(v3.y)) { fillBottomFlatTriangle(v1, v2, v3, color); }
    else if (int(v1.y) == int(v2.y)) { fillTopFlatTriangle(v1, v2, v3, color); }
    else
    {
        // general case - split the triangle in a topflat and bottom-flat one
        Point* v4 = new Point({
            (v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)),v2.y, 0
            });
        fillBottomFlatTriangle(v1, v2, *v4, color);
        fillTopFlatTriangle(v2, *v4, v3, color);
    }
}

void fillBottomFlatTriangle(Point v1, Point v2, Point v3, const vec3& color)
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

void fillTopFlatTriangle(Point v1, Point v2, Point v3, const vec3& color)
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
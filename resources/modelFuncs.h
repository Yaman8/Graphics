#pragma once

#include "Coord.h"
#include "transform.h"

void convertToScreen_model(std::vector<Triangle>& model)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            model[i].vertices[j] = model[i].vertices[j].Convert_to_Screen();
        }
    }
}

void translate_model(std::vector<Triangle>& model, Point pt)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            transate_polygon(model[i].vertices[j], pt); // translate the cube back to its original position
        }
    }
}

void scale_model(std::vector<Triangle>& model, Point pt)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scale_polygon(model[i].vertices[j], pt);
        }
    }
}

void rotate_model(std::vector<Triangle>& model, float angle)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rotateX(model[i].vertices[j], angle);
            rotateY(model[i].vertices[j], angle);
            //rotateZ(model[i].vertices[j], angle);
        }
    }
}

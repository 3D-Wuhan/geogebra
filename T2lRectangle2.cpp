//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "T2lRectangle2.h"

using namespace T2l;

//=============================================================================
Rectangle2::Rectangle2( const Point2F& origin, const Vector2F& width, double height,
                        EConstruct construct) :
    origin_(origin),
    width_(width),
    height_(height)
{
    if ( construct == RC_CENTER) originIsCenter_();
}

//=============================================================================
void Rectangle2::originIsCenter_()
{
    Vector2F dw = width_;
    Vector2F dh = up_();

    dw.multiply(-0.5);
    dh.multiply(-0.5);

    origin_.add(dw);
    origin_.add(dh);
}

//=============================================================================
Point2F Rectangle2::point(int index) const
{
    while ( index < 0 ) index += 4;
    while ( index > 3 ) index -= 4;

    Point2F result = origin_;

    switch (index)
    {
    case 1:
        result.add(width_);
        break;
    case 2:
        result.add(width_);
    case 3:
        result.add(up_());
        break;
    case 0:
    default:
        break;
    }

    return result;
}

//=============================================================================
Point2F Rectangle2::point( const Point2F& params) const
{
    Vector2F dir(width_);
    dir.multiply(params.x());

    Vector2F up(up_());
    up.multiply(params.y());

    Point2F result(origin_);
    result.add(dir);
    result.add(up);

    return result;
}

//=============================================================================
Vector2F Rectangle2::up_() const
{
    Vector2F result = width_;
    result.setPerpendLeft();
    result.setLength(height_);
    return result;
}

//=============================================================================
Point2F Rectangle2::center() const
{
    Point2F result;

    Vector2F dir2 = dir();
    dir2.multiply(0.5);
    result.add(dir2);

    Vector2F up2 = up();
    up2.multiply(0.5);
    result.add(up2);

    return result;
}

//=============================================================================

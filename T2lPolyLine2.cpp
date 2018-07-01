//
// Copyright (C) 2015, 2017 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lPolyLine2.h"
#include "T2lAngle.h"

using namespace T2l;

//=============================================================================
PolyLine2::PolyLine2(bool closed) :
    closed_(closed)
{
}

//=============================================================================
Point2F PolyLine2::getPoint(double parameter)
{
    if ( count() < 1 ) return Point2F();
    if ( count() < 2)  return get(0);

    int index = parameter;

    Vector2F offset(get(index), get(index+1));
    offset.multiply(parameter-(double)index);

    Point2F result(get(index));
    result.add(offset);
    return result;
}

//=============================================================================
void PolyLine2::offset(PolyLine2& result, double offsetArg)
{
    result.closed_ = closed_;

    for ( long i = 0; i < points_.count(); i++ ) {
        result.points().add( offsetVertex(i, offsetArg));
    }
}

//===================================================================
int PolyLine2::vertex(double parameter)
{
    assert( points().count() >= 1 );

    int result = (int)parameter;

    if ( result < 0 ) return 0;
    if ( result > points().count()-1 ) return points().count()-1;

    return result;
}

//=============================================================================
Point2F PolyLine2::offsetVertex(int /*index*/, double /*offset*/)
{
    // TODO
    return Point2F(0,0);
}

//=============================================================================
Line2 PolyLine2::segmentGet(int index)
{
    if ( index < 0 ) return Line2(Point2F(), Point2F());
    if ( index >= segmentCount() ) return Line2(Point2F(), Point2F());

    return Line2(points().get(index), points().get(index+1));
}

//=============================================================================
double PolyLine2::length()
{
    double result = 0;

    for (int i = 0; i < segmentCount(); i++) {
        result += segmentGet(i).length();
    }

    return result;
}

//=============================================================================

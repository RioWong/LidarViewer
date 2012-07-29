/***********************************************************************
PlanePrimitive - Class for planes extracted from point clouds.
Copyright (c) 2007-2011 Oliver Kreylos

This file is part of the LiDAR processing and analysis package.

The LiDAR processing and analysis package is free software; you can
redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

The LiDAR processing and analysis package is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with the LiDAR processing and analysis package; if not, write to the
Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
02111-1307 USA
***********************************************************************/

#ifndef PLANEPRIMITIVE_INCLUDED
#define PLANEPRIMITIVE_INCLUDED

#include <Geometry/Point.h>
#include <Geometry/Plane.h>
#include <GL/gl.h>
#include <GL/GLObject.h>

#include "Primitive.h"

/* Forward declarations: */
namespace Cluster {
class MulticastPipe;
}
class LidarOctree;

class PlanePrimitive:public Primitive,public GLObject
	{
	/* Embedded classes: */
	public:
	typedef Geometry::Plane<Scalar,3> Plane; // Type for plane equations
	
	private:
	struct DataItem:public GLObject::DataItem
		{
		/* Elements: */
		public:
		GLuint displayListId; // Base ID of the display lists containing the plane's surface and grid
		
		/* Constructors and destructors: */
		DataItem(void);
		virtual ~DataItem(void);
		};
	
	/* Elements: */
	private:
	Plane plane; // Equation of the extracted plane
	Point points[4]; // Corner points of a rectangle bounding the selected points
	int numX,numY; // Number of grid lines to render along the plane's x and y directions to achieve a mostly square grid
	
	/* Constructors and destructors: */
	public:
	PlanePrimitive(const LidarOctree* octree,const Vector& translation,Cluster::MulticastPipe* pipe); // Creates plane by processing selected points from the given octree; writes result to given pipe if !=0
	PlanePrimitive(Cluster::MulticastPipe* pipe); // Creates plane by reading plane data from given pipe
	PlanePrimitive(IO::File& file,const Vector& translation); // Reads a plane primitive from a binary file
	
	/* Methods: */
	virtual Scalar pick(const Point& pickPoint,Scalar maxPickDistance) const;
	virtual void initContext(GLContextData& contextData) const;
	virtual void glRenderAction(GLContextData& contextData) const;
	virtual void write(IO::File& file,const Vector& translation) const;
	const Plane& getPlane(void) const // Returns the equation of the extracted plane
		{
		return plane;
		};
	const Point& getPoint(int index) const // Returns one of the rectangle's corners
		{
		return points[index];
		};
	};

#endif

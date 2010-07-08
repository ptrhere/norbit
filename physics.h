/*----------------------------------------------------------------------------

2D Physics Test Program - a cheesy test harness for 2D physics

by Chris Hecker for my Game Developer Magazine articles.  See my homepage
for more information.

NOTE: This is a hacked test program, not a nice example of Windows programming.
physics.cpp the only part of this you should look at!!!

This material is Copyright 1997 Chris Hecker, All Rights Reserved.
It's for you to read and learn from, not to put in your own articles
or books or on your website, etc.  Thank you.

Chris Hecker
checker@d6.com
http://www.d6.com/users/checker

*/

/*----------------------------------------------------------------------------

physics.h - The header for the physics demo.

10/15/96 - checker

*/

#if !defined(PHYSICS_H)
#define PHYSICS_H

// explicit dependencies
#include "math2d.h"



/*----------------------------------------------------------------------------

Declarations for physics code.

*/

struct rigid_body
{
	real Width, Height;
	real OneOverMass, OneOverCMMomentOfInertia;
	real CoefficientOfRestitution;

	enum { NumberOfConfigurations = 2 };

	struct configuration
	{
		vector_2 CMPosition;
		real Orientation;

		vector_2 CMVelocity;
		real AngularVelocity;

		vector_2 CMForce;
		real Torque;

		struct bounding_box
		{
			vector_2 aVertices[4];

		} BoundingBox;

	} aConfigurations[NumberOfConfigurations];
};

class simulation_world
{
public:
	
	simulation_world( real WorldWidth, real WorldHeight );

	void Simulate( real DeltaTime );
	void Render( void );
	
	~simulation_world( void );


/*----------------------------------------------------------------------------

various forces you can add to the system

@todo need to figure out units here so these numbers mean something

*/

int WorldSpringActive;		// spring goes from body 0: vertex 0 to origin

vector_2 WorldSpringAnchor;
static real const Kws = 30.0f;			// Hooke's spring constant
static real const Kwd = 5.0f;	

int BodySpringActive;		// spring goes from body 0 to body 1
static real const Kbs = 10.0f;			// Hooke's spring constant
static real const Kbd = 5.0f;			// damping constant
int Body0SpringVertexIndex;
int Body1SpringVertexIndex;

int GravityActive ;
vector_2 Gravity;

int DampingActive;
static real const Kdl = 2.50f;		// linear damping factor
static real const Kda = 1400.0f;		// angular damping factor






private:

	enum collision_state
	{
		Penetrating,
		Colliding,
		Clear
	} CollisionState;

	vector_2 CollisionNormal;
	int CollidingBodyIndex;
	int CollidingCornerIndex;

	int SourceConfigurationIndex;
	int TargetConfigurationIndex;

	void ComputeForces( int ConfigurationIndex );
	void Integrate( real DeltaTime );
	collision_state CheckForCollisions( int ConfigurationIndex );
	void ResolveCollisions( int ConfigurationIndex );
	void CalculateVertices( int ConfigurationIndex );

	real WorldWidth, WorldHeight;

	enum { NumberOfWalls = 5 };
	struct wall
	{
		// define wall by plane equation
		vector_2 Normal;		// inward pointing
		real c;					// ax + by + c = 0

		// points for drawing wall
		vector_2 StartPoint;
		vector_2 EndPoint;
	} aWalls[NumberOfWalls];

	enum { NumberOfBodies = 2 };
	rigid_body aBodies[NumberOfBodies];
};

#endif

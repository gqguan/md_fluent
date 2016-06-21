/********************************************************************
 This UDF is an implementation of the species sink/source near the
  wall boundary condition. 
 It's a preliminary use for membrane distillation.
********************************************************************/
/******************************************************************** 
 Allocate the appropriate number (1) of memory location(s) in the 
  User-Defined Memory dialog box in ANSYS FLUENT
********************************************************************/

#include "udf.h"
#include "mem.h"
#include "metric.h"

DEFINE_SOURCE(evap_adj_membr, i_cell, t_cell, dS, eqn)
{
	Domain *domain; 
	Thread *t_FeedInterface; // pointer of the thread of faces
	face_t i_face = -1; 
	cell_t i_cell0, i_cell1 = -1; // indexes of adjacent cells for boundary identification
	real source;

	domain = Get_Domain(1); // explicit declaration of mixture
	t_FeedInterface = Lookup_Thread(domain, 13); // explicit get the boundary, id of 13 should be consisted with GUI display

	if (THREAD_ID(t_cell) == 5) // check the zone, id of 5 should be shown at GUI display
	{
		i_cell0 = F_C0(i_face, t_FeedInterface); // return the cell index of adjacent face, ref. "3.2.5 connectivity macro"
		i_cell1 = F_C1(i_face, t_FeedInterface); // return none at the boundary
		if (i_cell1 == -1)
		{
			source = 0.01;
		}
		else
		{
			source = 0.;
		}
	}
  dS[eqn] = 0.;
  return source;
}
/*BHEADER**********************************************************************
 * Copyright (c) 2006   The Regents of the University of California.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision: 1.1 $
 ***********************************************************************EHEADER*/



 
#include "headers.h"
 
/*--------------------------------------------------------------------------
 * hypre_GeneratePartitioning:
 * generates load balanced partitioning of a 1-d array
 *--------------------------------------------------------------------------*/
/* for multivectors, length should be the (global) length of a single vector.
 Thus each of the vectors of the multivector will get the same data distribution. */

int
hypre_GeneratePartitioning(HYPRE_BigInt length, int num_procs, HYPRE_BigInt **part_ptr)
{
   int ierr = 0;
   HYPRE_BigInt *part;
   HYPRE_BigInt size;
   int i, rest;


   part = hypre_CTAlloc(HYPRE_BigInt, num_procs+1);
   size = length / (HYPRE_BigInt)num_procs;
   rest = (int)(length - size*(HYPRE_BigInt)num_procs);
   part[0] = 0;
   for (i=0; i < num_procs; i++)
   {
	part[i+1] = part[i]+size;
	if (i < rest) part[i+1]++;
   }


   *part_ptr = part;
   return ierr;
}


/* This function differs from the above in that it only returns
   the portion of the partition belonging to the individual process - 
   to do this it requires the processor id as well AHB 6/05*/

int
hypre_GenerateLocalPartitioning(HYPRE_BigInt length, int num_procs, int myid, HYPRE_BigInt **part_ptr)
{


   int ierr = 0;
   HYPRE_BigInt *part;
   HYPRE_BigInt size;
   int rest;

   part = hypre_CTAlloc(HYPRE_BigInt, 2);
   size = length /(HYPRE_BigInt)num_procs;
   rest = (int)(length - size*(HYPRE_BigInt)num_procs);

   /* first row I own */
   part[0] = size*(HYPRE_BigInt)myid;
   part[0] += (HYPRE_BigInt)hypre_min(myid, rest);
   
   /* last row I own */
   part[1] =  size*(HYPRE_BigInt)(myid+1);
   part[1] += (HYPRE_BigInt)hypre_min(myid+1, rest);
   part[1] = part[1] - 1;

   /* add 1 to last row since this is for "starts" vector */
   part[1] = part[1] + 1;
   

   *part_ptr = part;
   return ierr;
}

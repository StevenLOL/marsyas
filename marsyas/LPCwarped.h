/*
** Copyright (C) 1998-2005 George Tzanetakis <gtzan@cs.uvic.ca>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/


/** 
\class LPCwarped
\brief Compute Warped LPC coefficients, Pitch and Power [STILL UNDER TESTING!].

Linear Prediction Coefficients (LPC). Features commonly used 
in Speech Recognition research. This class is a modification of the original
Marsyas0.1 LPC class. The following differences apply: 
- order now reflects the LPC order (and returns <order> coefficients plus pitch and gain)
- It is possible to define a pole-shifting parameter (gamma - default value = 1.0)
- It is possible to define a warping factor, lambda (defualt value = 0 => no warping)

Lu�s Gustavo Martins - lmartins@inescporto.pt
May 2006
*/

#ifndef MARSYAS_LPCWARPED_H
#define MARSYAS_LPCWARPED_H

#include "MarSystem.h"

namespace Marsyas
{

class LPCwarped: public MarSystem
{
private: 
	void addControls();
	void localUpdate();

	mrs_natural order_;

	realvec Zs_;
	realvec temp_;
	mrs_real pitch_;
	mrs_real power_;
	
	/**Warped autocorrelation for LPC calculation
	*Based on the code from: http://www.musicdsp.org/showone.php?id=137
	*Also estimates the pitch (only tested for lambda = 0), and updates the pitch_ member variable
	*@param in input audio frame
	*@param r autocorrelation output vector size (LPCorder + 1)
	*@param lambda frequency resolution (warp)
	*/
	void autocorrelationWarped(realvec& in, realvec& r, mrs_real lambda);

	/**Levinson-Durbin Recursion Algorithm
	*Based on the code from: http://www.musicdsp.org/showone.php?id=137
	*@param r input vector of autocorrelation coeffs
	*@param a output vector with the alpha LPC coeffs
	*@param k output vector with the reflection coeffs
	*/
	void LevinsonDurbin(realvec& r, realvec& a, realvec& k);

	/**LPC RMS Prediction Error
	*Updates the power_ member variable with the calculated value of the RMS perdiction error
	*@param data audio frame
	*@param coeffs LPC alpha coeffs
	*/
	void predictionError(realvec& data, realvec& coeffs);

public:
	LPCwarped(std::string name);
	~LPCwarped();

	MarSystem* clone() const;  

	void process(realvec& in, realvec& out);
};

}//namespace Marsyas

#endif




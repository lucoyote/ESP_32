/*
 * CLedStrip.h
 *
 *  Created on: 08 mar 2018
 *      Author: luca
 */

#ifndef MAIN_CLEDSTRIP_H_
#define MAIN_CLEDSTRIP_H_

#include <cstdlib>

class CLedStrip
{
public:
	CLedStrip(unsigned int  iLeds);
	virtual ~CLedStrip();

	void SetPixel (unsigned int iIndex, unsigned char R, unsigned char G, unsigned char B);


private:
	unsigned int  m_leds;
	unsigned char * m_buffer;

};

#endif /* MAIN_CLEDSTRIP_H_ */

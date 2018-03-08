/*
 * CLedStrip.cpp
 *
 *  Created on: 08 mar 2018
 *      Author: luca
 */

#include "CLedStrip.h"

CLedStrip::CLedStrip(unsigned int iLeds)
{
	m_leds = iLeds;
	m_buffer = (unsigned char *) malloc (iLeds * 3);

}

CLedStrip::~CLedStrip()
{
	if (m_buffer)
		delete m_buffer;

}
void CLedStrip::SetPixel (unsigned int iIndex, unsigned char R, unsigned char G, unsigned char B)
{
	if (m_buffer && iIndex < m_leds)
	{
		unsigned int iBufferIndex = iIndex *3;
		m_buffer[iBufferIndex++] = R;
		m_buffer[iBufferIndex++] = G;
		m_buffer[iBufferIndex] = B;
	}
}


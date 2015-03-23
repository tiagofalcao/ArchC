/**
 * @file      ac_tlm_intr_port.cpp
 * @author    Thiago Massariolli Sigrist
 * 
 * @author    The ArchC Team
 *            http://www.archc.org/
 *
 *            Computer Systems Laboratory (LSC)
 *            IC-UNICAMP
 *            http://www.lsc.ic.unicamp.br/
 * 
 * @version   2.0alpha1
 * @date      Fri, 24 Mar 2006 16:34:45 -0300
 * 
 * @brief     ArchC TLM interrupt (slave) port implementation.
 * 
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
 * 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 */

//////////////////////////////////////////////////////////////////////////////

// Standard includes

// SystemC includes

// ArchC includes
#include "ac_tlm_intr_port.H"

//////////////////////////////////////////////////////////////////////////////

// using statements

//////////////////////////////////////////////////////////////////////////////

// Forward class declarations, needed to compile

//////////////////////////////////////////////////////////////////////////////

// Constructors

/**
 * Default constructor.
 *
 * @param nm Port name.
 * @param hnd Interrupt handler for this port.
 *
 */
ac_tlm_intr_port::ac_tlm_intr_port(char const* nm, ac_intr_handler& hnd) :
  handler(hnd),
  name(nm) { bind(*this); }

//////////////////////////////////////////////////////////////////////////////

// Methods

/**
 * TLM transport function.
 *
 * @param req ArchC TLM protocol request packet.
 *
 * @return ArchC TLM protocol response packet.
 *
 */
ac_tlm_rsp ac_tlm_intr_port::transport(const ac_tlm_req& req) {
  ac_tlm_rsp rsp;

  rsp.req_type = req.type;
  rsp.data = req.data;

  if (req.type == WRITE) {
    rsp.status = SUCCESS;
    handler.handle(req.data);
  }
  else {
    rsp.status = ERROR;
  }

  return rsp;
}

//////////////////////////////////////////////////////////////////////////////

// Destructors

/**
 * Default (virtual) destructor.
 * @return Nothing.
 */
ac_tlm_intr_port::~ac_tlm_intr_port() {}

//////////////////////////////////////////////////////////////////////////////


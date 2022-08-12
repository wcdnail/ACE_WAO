
//=============================================================================
/**
 *  @file    cdr_op_ch.cpp
 *
 *  Visitor generating code for CDR operators for maps. This uses
 *  compiled marshaling.
 *
 *  @author Tyler Mayoff
 */
//=============================================================================

#include "map.h"

// ***************************************************************************
// Map visitor for generating CDR operator declarations in the client header
// ***************************************************************************

be_visitor_map_cdr_op_ch::be_visitor_map_cdr_op_ch (
    be_visitor_context *ctx) : be_visitor_decl (ctx)
{
}

int
be_visitor_map_cdr_op_ch::visit_map (be_map *)
{
  return 0;
}

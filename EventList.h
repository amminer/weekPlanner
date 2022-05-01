#pragma once

#include"Event.h"

/* Amelia Miner
 * 04/29/22
 * cs 202 section 003
 * PROGRAM #:	2
 * FILE:		EventList.h
 * PURPOSE:		Class EventList uses STL containers (a list of arrays) to manage a
 *				collection of Event objects, limiting addition of new events if
 *				their WeekdayTime members create a scheduling conflict with an
 *				existing event, except that a dinner and a flight can occur
 *				simultaneously, though no more than one of any event type can
 *				be scheduled for overlapping times (you can't have two flights
 *				at once, for example).
 */

class EventList
{
};

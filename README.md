>  vim: set ts=2 sw=2 tw=0 et :

# Electra

## Summary

* [Who Am I?](#who-am-i-)
* [Functionalities](#functionalities)
* [Examples](#examples)

## Who Am I?

<img align="left" width="200px" src="doc/character/electra.png"/>

Hello there, my name is **Electra**, have you heard of the amazing world of
Field-Coupled Nanocomputing? You can have an overview of the subject
in this [link](#).

Completely written using generic programming in C++, I serve as a  library
for working with the placement and routing problem in Field-Coupled
Nanocomputing.

As mentioned previously, I have no defined types, it is up to you
to determine what is the more appropriate for your use case,
in my documentation I give some examples about this.

I was written following the project guidelines from my friend,
[Anubis](https://formigoni.gitlab.io/anubis/), he is not so scary,
and can guide you to follow consistent project conventions throughout
your C++ project.


## Functionalities

You can read the full api documentation in my [gitlab pages](#).

For a quick summary, here's my list of features:

* Placement Management:
  * Redundancy
    * Get a placement id from a position.
    * Get a position from a placement id.
* Wire compaction:
  * (3,0),(2,0),...,(10,0) becomes (3,0),**(1,0)**,(10,0) below the wraps,
  * The highlighted item is a direction to go until
    reaching the final coordinate.
  * Furthermore, you do not need to worry about this language, all the
    encoding from one form to another is done automatically.
* [Json](https://www.json.org/) support:
  * Write placement and routing information using
    the json format.
  * Write statistics using the json format.
    * Number of wires used.
    * Area occupied exclusively by the wires.
    * Area occupied exclusively by the placements.
* Get the overall area of the placed and routed circuit at constant
  cost at any point in time.

## Examples

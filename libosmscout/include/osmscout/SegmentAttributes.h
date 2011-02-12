#ifndef OSMSCOUT_SEGMENTATTRIBUTES_H
#define OSMSCOUT_SEGMENTATTRIBUTES_H

/*
  This source is part of the libosmscout library
  Copyright (C) 2010  Tim Teulings

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/

#include <osmscout/FileScanner.h>
#include <osmscout/FileWriter.h>
#include <osmscout/Progress.h>
#include <osmscout/Tag.h>
#include <osmscout/TypeConfig.h>

namespace osmscout {

  class SegmentAttributes
  {
  public:
    // Common flags
    const static uint16_t hasTags         = 1 <<  0; //! We have additional tags stored on disk
    const static uint16_t hasName         = 1 <<  1; //! We have a name
    const static uint16_t hasRef          = 1 <<  2; //! We have reference name
    const static uint16_t isArea          = 1 <<  3; //! We are an area (or a way if not set)

    // Area flags
    const static uint16_t isBuilding      = 1 << 15; //! We are a building

    // Way flags
    const static uint16_t hasRestrictions = 1 <<  8; //! We have restrictions
    const static uint16_t hasWidth        = 1 <<  9; //! We have width
    const static uint16_t hasLayer        = 1 << 10; //! We have optional layer information
    const static uint16_t isBridge        = 1 << 11; //! We are a bridge
    const static uint16_t isTunnel        = 1 << 12; //! We are a tunnel
    const static uint16_t startIsJoint    = 1 << 13; //! Start node is a joint node
    const static uint16_t endIsJoint      = 1 << 14; //! End node is a joint node
    const static uint16_t isOneway        = 1 << 15; //! We are a oneway (in way direction)

  public:
    TypeId                    type;  //! type of the way/relation
    uint16_t                  flags;
    std::string               name;  //! name
    std::string               ref;   //! reference name (normally drawn in a plate)
    int8_t                    layer; //! layer to draw on
    uint8_t                   width; //! width of way
    std::vector<Tag>          tags;  //! list of preparsed tags

  public:
    inline SegmentAttributes()
    : type(typeIgnore),
      flags(0),
      layer(0),
      width(0)
    {
      // no code
    }

    inline TypeId GetType() const
    {
      return type;
    }

    inline uint16_t GetFlags() const
    {
      return flags;
    }

    inline bool IsArea() const
    {
      return (flags & isArea)!=0;
    }

    inline std::string GetName() const
    {
      return name;
    }

    inline std::string GetRefName() const
    {
      return ref;
    }

    inline int8_t GetLayer() const
    {
      return layer;
    }

    inline uint8_t GetWidth() const
    {
      return width;
    }

    inline bool IsBuilding() const
    {
      return (flags & isBuilding)!=0;
    }

    inline bool IsBridge() const
    {
      return (flags & isBridge)!=0;
    }

    inline bool IsTunnel() const
    {
      return (flags & isTunnel)!=0;
    }

    inline bool IsOneway() const
    {
      return (flags & isOneway)!=0;
    }

    inline bool StartIsJoint() const
    {
      return (flags & startIsJoint)!=0;
    }

    inline bool EndIsJoint() const
    {
      return (flags & endIsJoint)!=0;
    }

    inline bool HasRestrictions() const
    {
      return (flags & hasRestrictions)!=0;
    }

    bool SetTags(Progress& progress,
                 Id id,
                 bool isArea,
                 std::vector<Tag>& tags,
                 bool& reverseNodes);

    bool Read(FileScanner& scanner);
    bool Write(FileWriter& writer) const;
  };
}

#endif

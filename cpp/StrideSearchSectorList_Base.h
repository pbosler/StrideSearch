#ifndef _STRIDE_SEARCH_SECTOR_LIST_BASE_H_
#define _STRIDE_SEARCH_SECTOR_LIST_BASE_H_

#include "StrideSearch_Config.h"
#include "StrideSearch_TypeDefs.h"
#include "StrideSearchData_Base.h"
#include "StrideSearchWorkspaceDict.h"
#include "StrideSearchIDCriteria_Base.h"
#include "StrideSearchSector.h"
#include <vector>
#include <memory>

namespace StrideSearch {

/// A SectorList is the data structure used by driver programs to conduct searches of data sets.
/**
    SectorList is responsible for 
    1. Creating Sectors within a given search region defined as a rectangle
    in latitude-longitude space.
    2. Linking each sector to the data points and indices within the file associated with an StrideSearchData_Base subclass.
    3. Providing a control structure (loop) for the per-timestep search.
*/
class SectorList {
    public:
        /// Constructor. Inputs are the boundaries of a search region, and a sector radius in kilometers.
        /**
            @param sb southern latitudinal boundary, in degrees
            @param nb norhern latitudinal boundary, in degrees
            @param wb western longitudinal boundary, in degrees
            @param eb eastern longitudinal boundary, in degrees
        */
        SectorList(scalar_type sb, scalar_type nb, scalar_type wb, scalar_type eb, scalar_type sector_radius_km);
        virtual ~SectorList() {};
        
        /// Return the number of sectors in a SectorList
        inline int nSectors() const {return sectors.size();}
        
        /// Return a vector of all Sector centers.
        std::vector<ll_coord_type> listSectorCenters() const;
        
        std::string sectorInfoString(const index_type secInd) const;
        
        std::string infoString() const;
        
    protected: 
        scalar_type southBnd;
        scalar_type northBnd;
        scalar_type westBnd;
        scalar_type eastBnd;
        scalar_type radius;
        
        scalar_type lat_stride_deg;
        
        index_type nStrips;
        std::vector<scalar_type> lon_strides_deg;
        
        std::vector<std::unique_ptr<Sector>> sectors;
        
        /// Links each sector to the data points within its boundaries.
        /***
            Pure virtual function -- its implementation depends on the data set and must be handled by subclasses.
        */
        virtual void linkSectorsToData(StrideSearchData* ssdata_ptr) = 0;
        
        
};


}

#endif

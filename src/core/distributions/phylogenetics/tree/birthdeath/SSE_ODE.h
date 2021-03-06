#ifndef SSE_ODE_H
#define SSE_ODE_H

#include "AbstractBirthDeathProcess.h"
#include "RateMatrix.h"

#include <vector>
#include <boost/array.hpp>

typedef std::vector< double > state_type;

namespace RevBayesCore {
    
    /**
     * @brief Multi-rate cladogenetic birth-death ODE.
     *
     *
     * This class represents the ordinary differential equations for the character dependent
     * cladogenetic multi-rate birth-death process (ClaSSE: Goldberg and Igic, 2012)
     * Will Freyman 6/22/16
     *
     */
    class SSE_ODE {
        
    public:
        
        SSE_ODE( const std::vector<double> &m, const RateGenerator* q, double r, bool backward_time, bool extinction_only);
        
        void operator() ( const state_type &x , state_type &dxdt , const double t );
        
        void            setEventMap( const std::map<std::vector<unsigned>, double> &e );
        void            setSpeciationRate( const std::vector<double> &s );
        void            setSerialSamplingRate( const std::vector<double> &s );
        
    private:
        
        std::vector<double>                         mu;                                 //!< vector of extinction rates, one rate for each character state
        std::vector<double>                         lambda;                             //!< vector of speciation rates, one rate for each character state
        std::vector<double>                         psi;                                //!< vector of fossilization rates, one rate for each character state
        size_t                                      num_states;                         //!< the number of character states = q->getNumberOfStates()
        const RateGenerator*                        Q;                                  //!< anagenetic rate matrix
        std::map<std::vector<unsigned>, double>     event_map;                          //!< cladogenetic event map, with the structure pair< [ancestor_state, daughter_1_state, daughter_2_state], speciation_rate >
        double                                      rate;                               //!< clock rate for anagenetic change
        
        // flags to modify behabior
        bool                                        extinction_only;                    //!< calculate only extinction probabilities
        bool                                        use_speciation_from_event_map;      //!< do we use the speciation rates from the event map?
        bool                                        backward_time;                      //!< computation backward in time (otherwise forward)?

    };
    
}

#endif

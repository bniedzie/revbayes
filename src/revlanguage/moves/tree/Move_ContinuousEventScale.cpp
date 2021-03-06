#include "ArgumentRule.h"
#include "ArgumentRules.h"
#include "MetropolisHastingsMove.h"
#include "Move_ContinuousEventScale.h"
#include "ContinuousEventScaleProposal.h"
#include "RbException.h"
#include "RealPos.h"
#include "RlBoolean.h"
#include "RlTimeTree.h"
#include "TypedDagNode.h"
#include "TypeSpec.h"


using namespace RevLanguage;

/**
 * Default constructor.
 *
 * The default constructor does nothing except allocating the object.
 */
Move_ContinuousEventScale::Move_ContinuousEventScale() : Move()
{
    
}


/**
 * The clone function is a convenience function to create proper copies of inherited objected.
 * E.g. a.clone() will create a clone of the correct type even if 'a' is of derived type 'b'.
 *
 * \return A new copy of the move.
 */
Move_ContinuousEventScale* Move_ContinuousEventScale::clone(void) const
{
    
    return new Move_ContinuousEventScale(*this);
}


/**
 * Create a new internal move object.
 *
 * This function simply dynamically allocates a new internal move object that is
 * associated with the variable (DAG-node). The internal move object is created by calling its
 * constructor and passing the move-parameters (the variable and other parameters) as arguments of the
 * constructor. The move constructor takes care of the proper hook-ups.
 *
 */
void Move_ContinuousEventScale::constructInternalObject( void )
{
    // we free the memory first
    delete value;
    
    // now allocate a new scaling move
    double l = static_cast<const RealPos &>( lambda->getRevObject() ).getValue();
    double w = static_cast<const RealPos &>( weight->getRevObject() ).getValue();
    RevBayesCore::TypedDagNode<RevBayesCore::Tree>* tmp = static_cast<const TimeTree &>( tree->getRevObject() ).getDagNode();
    RevBayesCore::StochasticNode<RevBayesCore::Tree> *n = static_cast<RevBayesCore::StochasticNode<RevBayesCore::Tree> *>( tmp );
    
    bool t = static_cast<const RlBoolean &>( tune->getRevObject() ).getValue();
    
    RevBayesCore::Proposal *p = new RevBayesCore::ContinuousEventScaleProposal(n,l);
    value = new RevBayesCore::MetropolisHastingsMove(p,w,t);
    
}


/**
 * Get Rev type of object
 *
 * \return The class' name.
 */
const std::string& Move_ContinuousEventScale::getClassType(void)
{
    
    static std::string rev_type = "Move_ContinuousEventScale";
    
    return rev_type;
}


/**
 * Get class type spec describing type of an object from this class (static).
 *
 * \return TypeSpec of this class.
 */
const TypeSpec& Move_ContinuousEventScale::getClassTypeSpec(void)
{
    
    static TypeSpec rev_type_spec = TypeSpec( getClassType(), new TypeSpec( Move::getClassTypeSpec() ) );
    
    return rev_type_spec;
}


/**
 * Get the Rev name for the constructor function.
 *
 * \return Rev name of constructor function.
 */
std::string Move_ContinuousEventScale::getMoveName( void ) const
{
    // create a constructor function name variable that is the same for all instance of this class
    std::string c_name = "ContinuousEventScale";
    
    return c_name;
}


/**
 * Get the member rules used to create the constructor of this object.
 *
 * The member rules of the scale move are:
 * (1) the variable which must be a time-tree.
 *
 * \return The member rules.
 */
const MemberRules& Move_ContinuousEventScale::getParameterRules(void) const
{
    
    static MemberRules move_member_rules;
    static bool rules_set = false;
    
    if ( rules_set == false )
    {
        move_member_rules.push_back( new ArgumentRule( "tree", TimeTree::getClassTypeSpec()             , "The time-tree variable on which this move operates.", ArgumentRule::BY_REFERENCE, ArgumentRule::STOCHASTIC ) );
        move_member_rules.push_back( new ArgumentRule( "lambda", RealPos::getClassTypeSpec()            , "The scaling factor (strength) of the proposal.", ArgumentRule::BY_VALUE    , ArgumentRule::ANY, new Real(1.0) ) );
        move_member_rules.push_back( new ArgumentRule( "tune"  , RlBoolean::getClassTypeSpec()          , "Should we tune the scaling factor during burnin?", ArgumentRule::BY_VALUE    , ArgumentRule::ANY, new RlBoolean( true ) ) );
        
        /* Inherit weight from Move, put it after variable */
        const MemberRules& inherited_rules = Move::getParameterRules();
        move_member_rules.insert( move_member_rules.end(), inherited_rules.begin(), inherited_rules.end() );
        
        rules_set = true;
    }
    
    return move_member_rules;
}


/**
 * Get type-specification on this object (non-static).
 *
 * \return The type spec of this object.
 */
const TypeSpec& Move_ContinuousEventScale::getTypeSpec( void ) const
{
    
    static TypeSpec type_spec = getClassTypeSpec();
    
    return type_spec;
}


/**
 * Set a member variable.
 *
 * Sets a member variable with the given name and store the pointer to the variable.
 * The value of the variable might still change but this function needs to be called again if the pointer to
 * the variable changes. The current values will be used to create the distribution object.
 *
 * \param[in]    name     Name of the member variable.
 * \param[in]    var      Pointer to the variable.
 */
void Move_ContinuousEventScale::setConstParameter(const std::string& name, const RevPtr<const RevVariable> &var)
{
    
    if ( name == "tree" )
    {
        tree = var;
    }
    else if ( name == "lambda" )
    {
        lambda = var;
    }
    else if ( name == "tune" )
    {
        tune = var;
    }
    else
    {
        Move::setConstParameter(name, var);
    }
    
}






/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkLBFGSOptimizerTest.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/

#include <itkLBFGSOptimizer.h>
#include <itkPoint.h>


/** 
 *  The objectif function is the quadratic form:
 *
 *  1/2 x^T A x - b^T x
 *
 *  Where A is represented as an itkMatrix and 
 *  b is represented as a itkVector
 *
 *  The system in this example is:
 *
 *     | 3  2 ||x|   | 2|   |0|
 *     | 2  6 ||y| + |-8| = |0|
 *
 *
 *   the solution is the vector | 2 -2 |
 *
 */ 
class CostFunction : public itk::LightObject 
{
public:

  typedef CostFunction Self;
  typedef itk::LightObject  Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  itkNewMacro( Self );

  enum { SpaceDimension=2 };
  typedef itk::Point<double,SpaceDimension> ParametersType;
  typedef itk::Point<double,SpaceDimension> DerivativeType;
  typedef double MeasureType ;


  CostFunction() 
  {
  }

  const ParametersType & GetParameters(void) const 
  { 
    return m_Parameters;
  }

  double GetValue( const ParametersType & position ) const
  { 

    m_Parameters = position;

    double x = position[0];
    double y = position[1];

    std::cout << "GetValue ( " ;
    std::cout << x << " , " << y;
    std::cout << ") = ";

    double val = 0.5*(3*x*x+4*x*y+6*y*y) - 2*x + 8*y;

    std::cout << val << std::endl; 

    return val;
  }

  DerivativeType GetDerivative( const ParametersType & position ) const
  {

    double x = position[0];
    double y = position[1];

    std::cout << "GetDerivative ( " ;
    std::cout << x << " , " << y;
    std::cout << ") = ";

    DerivativeType grad;
    grad[0] = 3*x + 2*y -2;
    grad[1] = 2*x + 6*y +8;
    std::cout << "(" ; 
    std::cout << grad[0] <<" , ";
    std::cout << grad[1] << ")" << std::endl;
    return grad;
  }

private:

  mutable ParametersType m_Parameters;

};



int main() 
{
  std::cout << "Conjugate Gradient Optimizer Test \n \n";

  typedef  itk::LBFGSOptimizer< 
                                CostFunction >  OptimizerType;

  typedef  OptimizerType::InternalOptimizerType  vnlOptimizerType;

  
  
  // Declaration of a itkOptimizer
  OptimizerType::Pointer  itkOptimizer = OptimizerType::New();


  // Declaration of the CostFunction adaptor
  CostFunction costFunction;


  itkOptimizer->SetCostFunction( &costFunction );

  
  const double F_Tolerance      = 1e-3;  // Function value tolerance
  const double G_Tolerance      = 1e-4;  // Gradient magnitude tolerance 
  const double X_Tolerance      = 1e-8;  // Search space tolerance
  const double Epsilon_Function = 1e-10; // Step
  const int    Max_Iterations   =   100; // Maximum number of iterations


  vnlOptimizerType & vnlOptimizer = itkOptimizer->GetOptimizer();

  vnlOptimizer.set_f_tolerance( F_Tolerance );
  vnlOptimizer.set_g_tolerance( G_Tolerance );
  vnlOptimizer.set_x_tolerance( X_Tolerance ); 
  vnlOptimizer.set_epsilon_function( Epsilon_Function );
  vnlOptimizer.set_max_function_evals( Max_Iterations );

  vnlOptimizer.set_check_derivatives( 3 );
      
  const unsigned int SpaceDimension = 2;
  typedef itk::Point<double,SpaceDimension> ParametersType;
  ParametersType initialValue;

  // We start not so far from  | 2 -2 |
  initialValue[0] =  100;
  initialValue[1] = -100;

  itkOptimizer->SetInitialPosition( initialValue );
  itkOptimizer->StartOptimization();

  std::cout << "End condition   = " << vnlOptimizer.get_failure_code()    << std::endl;
  std::cout << "Number of iters = " << vnlOptimizer.get_num_iterations()  << std::endl;
  std::cout << "Number of evals = " << vnlOptimizer.get_num_evaluations() << std::endl;    
  std::cout << std::endl;

  ParametersType finalPosition;
  finalPosition = costFunction.GetParameters();
  std::cout << "Solution        = (";
  std::cout << finalPosition[0] << "," ;
  std::cout << finalPosition[1] << ")" << std::endl;  

  //
  // check results to see if it is within range
  //
  bool pass = true;
  double trueParameters[2] = { 2, -2 };
  for( unsigned int j = 0; j < 2; j++ )
    {
    if( vnl_math_abs( finalPosition[j] - trueParameters[j] ) > 0.01 )
      pass = false;
    }

  if( !pass )
    {
    std::cout << "Test failed." << std::endl;
    return EXIT_FAILURE;
    }

  std::cout << "Test passed." << std::endl;
  return EXIT_SUCCESS;





}




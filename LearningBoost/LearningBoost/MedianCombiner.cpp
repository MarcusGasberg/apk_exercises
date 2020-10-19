//
//#include "MedianCombiner.h"
//
//#include <iostream>
//#include <boost/signals2/signal.hpp>
//
//double product(double x, double y,double z) { return x * y * z; }
//double quotient(double x, double y,double z) { return x / y / z; }
//double sum(double x, double y,double z) { return x + y + z; }
//double difference(double x, double y,double z) { return x - y - z; }
//
//int main()
//{
//	boost::signals2::signal<double(double, double, double), median_combiner<double>> sig;
//	sig.connect(&product);
//	sig.connect(&quotient);
//	sig.connect(&sum);
//	sig.connect(&difference);
//
//	std::cout << "Median: " << sig(2, 3, 4) << std::endl;
//}
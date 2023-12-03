# solar-water-heater

## Building the program 
1. Extract the contents of SolarWaterHeaterSimulator.zip file 
2. Install boost library from the following link. Extract the .7z or .zip file in the same level as the Scalar directory https://www.boost.org/users/history/version_1_82_0.html 
3. Open the CMakeLists.txt file in Visual Studio using File | Open | CMake 
4. Build and run the program. 
Notes:  
a. If the user wishes to change the operating conditions (stream temperature, volumetric flow  rate) please refer to createExampleSimulationSystem() function in Simulation class and make  changes to the objects there. The design parameters of unit operation can also be modified in  the corresponding unit operation header files.  
b. The version of boost required to be downloaded would depend on the version of cmake in the  machine. The boost version 1_82_0 is compatible with Cmake version 3.27.0 or higher. If boost  version has to be changed, please update the version number in  
SolarWaterHeaterSimulator/CMakeLists.txt file as well. 


## Modeling assumptions
1. Temperature inside the storage tank and the solar water heater tank is considered uniform throughout the volume. The tank temperature in the heat balance calculations is approximated  to be equal to the tank outlet temperature. 
2. Startup dynamics such as pump startup, storage tank fill-up and solar panel fill-up are not  modeled. Steady state initial conditions are assumed. 
3. Pump volume is considered to be zero. 
4. Assuming no pressure loss across pipe connections. 
5. Heat transfer due to friction in the pump is considered negligible. 
6. Currently considering this to be a closed system. That is no supply or demand from the storage  tank is modeled yet.  
7. Variations to the inlet and outlet streams with respect to time are not modeled in the program  yet.


## Program assumptions 
1. The variables, design parameters of unit operations (volume, heat loss coefficient, efficiency, surface area, etc) and stream properties (density, specific heat capacity) are specified in the  same unit system. No unit conversion is implemented. 
2. There are no “dangling” streams or unit operation in the flowsheet. 


## Modeling approach 
1. Each unit operation – pump, storage tank and solar panel are defined as classes inheriting from  unit operation (refer UnitOperation directory) 
2. MassStream and EnergyStream are the classes defining the inlet and outlet streams connected  to unit operation. These streams derive from Stream class (refer Stream directory). 3. Inlet and outlet mass streams and energy streams are connected to each unit operation. These  streams are shared between unit operations (using shared pointers in c++). This way, the  topology is defined by just connecting the unit operations to the appropriate streams. 4. SimulationSystem class contains the list of pointers to the unit operations that form the system  to be simulated. The createExampleSimulationSystem() function in Simulation/Simulation.h defines the topology that is defined in the programming challenge. 

## Mathematical modeling approach 
1. Boost’s ODEint library is used to solve the system of equations 
2. Once the SimulationSystem (containing the topology of the system) is setup in the Simulation  class, the solve() function interacts with the odeint solver to start integrating the dynamics of  the system. 
3. The system is first initialized with the initialize() function in SimulationSystem. This function  calls the initialize() function in each unit operation to determine the initial values of the  variables.
4. Every time step, the solver is asked to integrate where it is provided with a callback function to  update the derivatives of the variables. 
5. After the solver performs a step, the new variable values are transferred back to the model  (SimulationSystem) which then updates the states of each stream connected to each unit  operation. 
6. Mass and Energy balance equations:


## Results 
• The heat inlet varies with respect to time in a sinusoidal wave.  
• The increase and decrease in outlet temperature of the solar water heater is almost in  synchrony with the variation with the heat flow.  
• The slight delay in the outlet temperature rise can be explained by the heat accumulation in the  heater.  
• Storage Tank inlet temperature (Solar Water Heater Inlet temperature) is reduced due to the heat loss in the storage tank.




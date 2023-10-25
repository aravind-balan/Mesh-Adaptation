config.title = "Mach 8.98 flow over a 2D cylinder"
print(config.title)
config.dimensions = 2

nsp, nmodes, gmodel = setGasModel('ideal-air-gas-model.lua')

Mach = 8.98
T_inf = 901 -- K
Twall = 300.00 -- K
R = 287.0 -- kJ/kg.K
gas = GasState:new{gmodel}
gas.T = T_inf
gmodel:updateTransCoeffs(gas)
gamma = gmodel:gamma(gas)
U_inf = Mach*math.sqrt(gamma*R*gas.T) -- m/s
p_inf = 476

inflow = FlowState:new{p=p_inf, T=T_inf, velx=U_inf}
-- initial = inflow

initial = FlowState:new{p= 9.71297e+006,T= 15432.4000, velx=0}

print("Inflow = ", inflow)
print("T = ", inflow.T, " Density = ", inflow.rho, "Acoustic Speed = ", inflow.a)
print("Inflow Mach Number = ", U_inf/inflow.a)

meshfile = UnstructuredGrid:new{filename="heg_cylinder.su2", fmt="su2text"}

boundary_conditions = {inlet=InFlowBC_Supersonic:new{flowState=inflow},
		       wall=WallBC_NoSlip_FixedT:new{Twall=300},
		       outlet=OutFlowBC_Simple:new{}}

block = FluidBlock:new{grid=meshfile, initialState=inflow, bcDict=boundary_conditions}

-- Now set some configuration options

config.max_step = 3000
config.cfl_value = 0.5
config.dt_plot = 1.5e-4
config.dt_history = 1.0e-5

config.adjust_invalid_cell_data = true

config.flux_calculator = "ausmdv"
config.interpolation_order = 2
config.apply_limiter = true
config.extrema_clipping = true

config.viscous = true
config.spatial_deriv_calc = "least_squares"
config.spatial_deriv_locn = "cells"

config.title = "Mach 1.2 flow over a NACA 0012 airfoil"
print(config.title)
config.dimensions = 2

nsp, nmodes, gm = setGasModel('ideal-gas.lua')
print("Gas Model set to Ideal Air. nsp = ", nsp, " nmodes = ", nmodes)
initial = FlowState:new{p=5955.0, T = 304.0, velx=0.0}
inflow = FlowState:new{p=101325.0, T = 300.0, velx=417.00}

print("Inflow = ", inflow)
print("T = ", inflow.T, " Density = ", inflow.rho, "Acoustic Speed = ", inflow.a)
print("Inflow Mach Number = ", 417.00/inflow.a)

meshfile = UnstructuredGrid:new{filename="mesh_NACA0012_inv.su2", fmt="su2text"}
boundary_conditions = {InFlowBC_ConstFlux:new{flowState=inflow}}

block = FluidBlock:new{grid=meshfile, initialState=inflow, bcDict=boundary_conditions}

-- block.bcList[farfield] = 
config.max_step = 3000

config.cfl_value = 0.5
config.dt_plot = 1.5e-4
config.dt_history = 1.0e-5


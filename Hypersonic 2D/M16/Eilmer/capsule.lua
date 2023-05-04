config.title = "Mach 16 over a capsule at 35000 m altitude"
print(config.title)
config.dimensions = 2

nsp, nmodes, gm = setGasModel('ideal-gas.lua')
print("Gas Model set to Ideal Air. nsp = ", nsp, " nmodes = ", nmodes)
initial = FlowState:new{p=557.7558, T = 237.0, velx=0.0}
inflow = FlowState:new{p=557.7558, T = 237.0, velx=4937.4092}

print("Inflow = ", inflow)
print("T = ", inflow.T, " Density = ", inflow.rho, "Acoustic Speed = ", inflow.a)
print("Inflow Mach Number = ", 4937.4092/inflow.a)

meshfile = UnstructuredGrid:new{filename="mesh_hypersonic_full.su2", fmt="su2text"}
boundary_conditions = {INFLOW=InFlowBC_Supersonic:new{flowState=inflow},
		       OUTFLOW=OutFlowBC_Simple:new{},
		       WALL=WallBC_WithSlip:new{}}

block = FluidBlock:new{grid=meshfile, initialState=inflow, bcDict=boundary_conditions}

-- block.bcList[farfield] = 
config.max_step = 3000

config.cfl_value = 0.2
config.dt_plot = 1.5e-4
config.dt_history = 1.0e-5


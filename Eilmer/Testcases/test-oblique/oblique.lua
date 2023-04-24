-- cone20.lua
-- Simple job-specification file for e4prep -- for use with Eilmer4
-- PJ & RG
-- 2015-02-24 -- adapted from the Python version of cone20
-- 2018-01-26 -- 4-blocks to test MPI flavour of code.
-- 2019-06-25 -- 8-blocks because that is the number of CPUs on my workstation.

-- We can set individual attributes of the global data object.
config.title = "Mach 1.5 flow over a 20 degree cone."
print(config.title)
config.dimensions = 2
config.axisymmetric = true

-- The gas model is defined via a gas-model file.
nsp, nmodes, gm = setGasModel('ideal-air-gas-model.lua')
print("GasModel set to ideal air. nsp= ", nsp, " nmodes= ", nmodes)
initial = FlowState:new{p=5955.0, T=304.0, velx=0.0}
inflow = FlowState:new{p=95.84e3, T=1103.0, velx=1000.0}

-- Demo: Verify Mach number of inflow and compute dynamic pressure.
print("inflow=", inflow)
print("T=", inflow.T, "density=", inflow.rho, "sound speed= ", inflow.a)
print("inflow Mach number=", 1000.0/inflow.a)
print("dynamic pressure q=", 1/2*inflow.rho*1.0e6)

grids = {}
grids[0] = UnstructuredGrid:new{filename="Oblique.su2", fmt="su2text"}

my_bcDict = {INFLOW=InFlowBC_Supersonic:new{flowState=inflow},
	     OUTFLOW=OutFlowBC_Simple:new{}
}

blks = {}
blks[0] = FluidBlock:new{grid=grids[0], initialState=inflow, bcDict=my_bcDict}

-- Do a little more setting of global data.
-- mpiDistributeBlocks{ntasks=12, dist="load-balance", preassign={[0]=1}}
config.max_time = 5.0e-3  -- seconds
config.max_step = 3000
-- config.dt_init = 1.0e-6
config.cfl_value = 0.5
config.dt_plot = 1.5e-4
config.dt_history = 10.0e-5
-- config.gasdynamic_update_scheme = "euler"
-- config.print_count = 100
-- config.cfl_count = 20
config.extrema_clipping = false

-- dofile("sketch-domain.lua")

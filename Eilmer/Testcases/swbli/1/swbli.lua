-- swbli.lua
-- Simulation of a shockwave/boundary layer interaction, based on T4
-- experiments by Eric Chang
-- https://doi.org/10.1017/jfm.2020.877
-- @author: NNG (13/06/22)

config.dimensions = 2
config.viscous = true
config.flux_calculator = "ausmdv"
config.turbulence_model = "spalart_allmaras_edwards"

-- Gas model and flow conditions Mach 7 Enthalpy
nsp, nmodes, gm = setGasModel('gm-air5.lua')
p_inf = 2624.0 -- Pa
u_inf = 2221.0 -- m/s
T_inf = 250.0  -- K

config.reacting = true
config.reactions_file = 'rr-kim-air5.lua'

-- Compute the gas state in physical units from its nondimensional description
gs = GasState:new{gm}
gs.T = T_inf
gs.p = p_inf
gs.massf = {N2=0.767, O2=0.233}
gm:updateThermoFromPT(gs)
gm:updateTransCoeffs(gs)

-- Use updated gas properties to estimate turbulence quantities
turb_lam_viscosity_ratio = 5.0 -- Fully turbulent, equation (8) from Allmaras (2012)
nu_inf = gs.mu/gs.rho
nuhat_inf = turb_lam_viscosity_ratio*nu_inf

inflow = FlowState:new{p=p_inf, velx=u_inf, T=T_inf, nuhat=nuhat_inf, massf={N2=0.767, O2=0.233}}

grid = UnstructuredGrid:new{filename="swbli.su2", fmt="su2text"}

-- FluidBlock:new

boundary_conditions = {	outlet=OutFlowBC_Simple:new{},
                       	lower=WallBC_NoSlip_FixedT:new{Twall=300.0, group="wall"},
                       	inlet=InFlowBC_Supersonic:new{flowCondition=inflow}}

blks = FluidBlock:new{grid=grid, initialState=inflow, bcList=boundary_conditions, bcDict=boundary_conditions}

identifyBlockConnections()

-- loads settings
config.boundary_groups_for_loads = "wall"
config.write_loads = true
config.with_local_time_stepping=true

SteadyStateSolver{
   use_preconditioner = true,
   precondition_matrix_type = "ilu",
   ilu_fill = 0,
   frozen_preconditioner_count = 20,
   
   use_scaling = true,
   use_complex_matvec_eval = true,
   use_physicality_check = true,
   
   number_total_steps = 2000,
   stop_on_relative_global_residual = 1.0e-5,

   -- Settings for FGMRES iterative solver
   max_outer_iterations = 40,
   max_restarts = 4,

   residual_based_cfl_scheduling = true,
   cfl_max = 1e4,

   -- Settings for start-up phase
   number_start_up_steps = 0,
   cfl0 = 1.0,
   eta0 = 0.01,
   sigma0 = 1.0e-50,

   -- Settings for inexact Newton phase
   cfl1 = 1.0,
   sigma1 = 1.0e-50,
   eta1 = 0.01,
   tau1 = 0.5,
   p1 = 0.7,

   -- Settings control write-out
   snapshots_count = 100,
   number_total_snapshots = 100,
   write_diagnostics_count = 1,
   write_loads_count = 100,
}

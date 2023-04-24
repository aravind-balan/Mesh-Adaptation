-- Unstructured Grid Example -- for use with Eilmer4
-- 2023-03-22 RJG, PJ, KAD

config.title = "Mach 1.5 flow over a 20 degree cone -- Unstructured Grid."
print(config.title)
config.dimensions = 2
config.axisymmetric = true
config.max_time = 5.0e-3  -- seconds
config.max_step = 3000
config.dt_plot = 1.5e-3
--
nsp, nmodes, gm = setGasModel('ideal-air-gas-model.lua')
inflow = FlowState:new{p=95.84e3, T=1103.0, velx=1000.0}
--
-- In the following table, the keys are not valid identifiers,
-- so we set the entries with keys as strings.
flowDict = {}
flowDict["initial-gas"] = FlowState:new{p=5955.0, T=304.0}
flowDict["inflow-gas"] = inflow
--
-- Set table entries in a different way
-- since the keys are valid identifiers.
bcDict = {
   INFLOW=InFlowBC_Supersonic:new{flowState=inflow},
   OUTFLOW=OutFlowBC_Simple:new{},
   SLIP_WALL=WallBC_WithSlip:new{},
   INTERIOR=ExchangeBC_MappedCell:new{list_mapped_cells=true},
   CONE_SURFACE=WallBC_WithSlip:new{},
}
--
makeFluidBlocks(bcDict, flowDict)

-- cone20-grid.lua
-- Simple grid-specification file for Eilmer4.
-- PJ 2021-03-16 adapted from the cone20.lua example.
-- Process with the command:
-- $ e4shared --prep-grid --job=cone20
--
config.dimensions = 2
--
-- f--e-----d
-- |  |     |
-- |  |     |
-- |  |  -/-c
-- a--b-/
a = {x=0.0, y=0.0}; b = {x=0.2, y=0.0}; c = {x=1.0, y=0.29118}
d = {x=1.0, y=1.0}; e = {x=0.2, y=1.0}; f = {x=0.0, y=1.0}
quad0 = CoonsPatch:new{p00=a, p10=b, p11=e, p01=f}
quad1 = AOPatch:new{p00=b, p10=c, p11=d, p01=e}
--
-- Mesh the patches, with particular discretisation and
-- register the grids for use in the simulation setup phase.
nx0 = 10; nx1 = 30; ny = 40
grid0 = StructuredGrid:new{psurface=quad0, niv=nx0+1, njv=ny+1}
grid0:set_tags{west="INFLOW"} -- Uppercase, just because we use that for SU2 bcs.
grid1 = StructuredGrid:new{psurface=quad1, niv=nx1+1, njv=ny+1}
grid1:set_tags{east="OUTFLOW"}

registerGrid{grid=grid0, fsTag="inflow-gas"}
registerGrid{grid=grid1, fsTag="initial-gas"}
identifyGridConnections()
--
dofile("sketch-domain.lua")

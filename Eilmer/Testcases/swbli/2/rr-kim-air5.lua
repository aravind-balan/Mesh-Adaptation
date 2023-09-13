species = {[0]='N2', [1]='O2', [2]='N', [3]='O', [4]='NO', }
config = {
  tempLimits = {lower=300.000000, upper=30000.000000},
  odeStep = {method='rkf', errTol=1.000000e-09},
  tightTempCoupling = true,
  maxSubcycles = 10000,
  maxAttempts = 4
}

reaction = {}
reaction[1] = {
  equation = "N2 + N2 <=> N + N + N2",
  type = "elementary",
  frc = {model='Arrhenius', A=1.216000000000e+14, n=-1.214000, C=1.132000000000e+05, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0,},
  reacCoeffs = { 2.000000e+00,},
  prodIdx = { 0, 2,},
  prodCoeffs = { 1.000000e+00, 2.000000e+00,},
  label = "N2diss",
}

reaction[2] = {
  equation = "N2 + O2 <=> N + N + O2",
  type = "elementary",
  frc = {model='Arrhenius', A=7.000000000000e+15, n=-1.600000, C=1.132000000000e+05, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 1,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 1, 2,},
  prodCoeffs = { 1.000000e+00, 2.000000e+00,},
  label = "N2diss",
}

reaction[3] = {
  equation = "N2 + NO <=> N + N + NO",
  type = "elementary",
  frc = {model='Arrhenius', A=7.000000000000e+15, n=-1.600000, C=1.132000000000e+05, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 4,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 2, 4,},
  prodCoeffs = { 2.000000e+00, 1.000000e+00,},
  label = "N2diss",
}

reaction[4] = {
  equation = "N2 + N <=> N + N + N",
  type = "elementary",
  frc = {model='Arrhenius', A=3.591000000000e+14, n=-1.226000, C=1.132000000000e+05, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 2,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 2,},
  prodCoeffs = { 3.000000e+00,},
  label = "N2diss",
}

reaction[5] = {
  equation = "N2 + O <=> N + N + O",
  type = "elementary",
  frc = {model='Arrhenius', A=3.000000000000e+16, n=-1.600000, C=1.132000000000e+05, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 3,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 2, 3,},
  prodCoeffs = { 2.000000e+00, 1.000000e+00,},
  label = "N2diss",
}

reaction[6] = {
  equation = "O2 + N2 <=> O + O + N2",
  type = "elementary",
  frc = {model='Arrhenius', A=3.354000000000e+09, n=-0.272600, C=5.950000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 1,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 0, 3,},
  prodCoeffs = { 1.000000e+00, 2.000000e+00,},
  label = "O2diss",
}

reaction[7] = {
  equation = "O2 + O2 <=> O + O + O2",
  type = "elementary",
  frc = {model='Arrhenius', A=1.117000000000e+19, n=-2.585000, C=5.950000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 1,},
  reacCoeffs = { 2.000000e+00,},
  prodIdx = { 1, 3,},
  prodCoeffs = { 1.000000e+00, 2.000000e+00,},
  label = "O2diss",
}

reaction[8] = {
  equation = "O2 + NO <=> O + O + NO",
  type = "elementary",
  frc = {model='Arrhenius', A=3.354000000000e+09, n=-0.272600, C=5.950000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 1, 4,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 3, 4,},
  prodCoeffs = { 2.000000e+00, 1.000000e+00,},
  label = "O2diss",
}

reaction[9] = {
  equation = "O2 + N <=> O + O + N",
  type = "elementary",
  frc = {model='Arrhenius', A=1.000000000000e+16, n=-1.500000, C=5.950000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 1, 2,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 2, 3,},
  prodCoeffs = { 1.000000e+00, 2.000000e+00,},
  label = "O2diss",
}

reaction[10] = {
  equation = "O2 + O <=> O + O + O",
  type = "elementary",
  frc = {model='Arrhenius', A=3.000000000000e+15, n=-1.500000, C=5.950000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 1, 3,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 3,},
  prodCoeffs = { 3.000000e+00,},
  label = "O2diss",
}

reaction[11] = {
  equation = "NO + M <=> N + O + M",
  type = "anonymous_collider",
  frc = {model='Arrhenius', A=1.450000000000e+09, n=0.000000, C=7.520000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 4,},
  reacCoeffs = { 1.000000e+00,},
  prodIdx = { 2, 3,},
  prodCoeffs = { 1.000000e+00, 1.000000e+00,},
  efficiencies = {
    [0]=1.000000e+00,
    [1]=1.000000e+00,
    [2]=6.648276e-01,
    [3]=6.648276e-01,
    [4]=6.648276e-01,
  },
  label = "NOdiss",
}

reaction[12] = {
  equation = "NO + O <=> O2 + N",
  type = "elementary",
  frc = {model='Arrhenius', A=8.400000000000e+06, n=0.000000, C=1.945000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 3, 4,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 1, 2,},
  prodCoeffs = { 1.000000e+00, 1.000000e+00,},
}

reaction[13] = {
  equation = "N2 + O <=> NO + N",
  type = "elementary",
  frc = {model='Arrhenius', A=6.400000000000e+11, n=-1.000000, C=3.840000000000e+04, rctIndex=-1},
  brc = {model='fromEqConst', rctIndex=-1},
  ec = {},
  reacIdx = { 0, 3,},
  reacCoeffs = { 1.000000e+00, 1.000000e+00,},
  prodIdx = { 2, 4,},
  prodCoeffs = { 1.000000e+00, 1.000000e+00,},
}


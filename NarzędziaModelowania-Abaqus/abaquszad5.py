# -*- coding: mbcs -*-
# Do not delete the following import lines
from abaqus import *
from abaqusConstants import *
import __main__

def Macro1(alpha1,alpha2,alpha3):
    import section
    import regionToolset
    import displayGroupMdbToolset as dgm
    import part
    import material
    import assembly
    import step
    import interaction
    import load
    import mesh
    import optimization
    import job
    import sketch
    import visualization
    import xyPlot
    import displayGroupOdbToolset as dgo
    import connectorBehavior
	
    mdb.models['Model-1'].setValues(absoluteZero=-273.15, 
        stefanBoltzmann=5.67037E-11)
    s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=2000.0)
    g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
    s.setPrimaryObject(option=STANDALONE)
    s.CircleByCenterPerimeter(center=(0.0, 0.0), point1=(-87.5, 125.0))
    s.CircleByCenterPerimeter(center=(0.0, 0.0), point1=(-212.5, 150.0))
    s.RadialDimension(curve=g[2], textPoint=(-455.602355957031, -27.0244750976563), 
        radius=425.0)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=1385.61, 
        farPlane=2385.63, width=3329.17, height=1470.83, cameraPosition=(
        785.488, 118.461, 1885.62), cameraTarget=(785.488, 118.461, 0))
    s.RadialDimension(curve=g[3], textPoint=(-647.020812988281, -154.377532958984), 
        radius=995.0)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=1065.35, 
        farPlane=2705.89, width=6180.98, height=2730.77, cameraPosition=(
        1945.83, -55.0143, 1885.62), cameraTarget=(1945.83, -55.0143, 0))
    session.viewports['Viewport: 1'].view.setValues(cameraPosition=(468.55, 
        83.8385, 1885.62), cameraTarget=(468.55, 83.8385, 0))
    session.viewports['Viewport: 1'].view.setValues(width=5810.12, height=2566.93, 
        cameraPosition=(446.852, 74.1188, 1885.62), cameraTarget=(446.852, 
        74.1188, 0))
    p = mdb.models['Model-1'].Part(name='coil', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['coil']
    p.BaseSolidExtrude(sketch=s, depth=1200.0)
    s.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['coil']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4174.01, 
        farPlane=8614.04, width=4544.11, height=2007.6, cameraUpVector=(
        -0.416279, 0.557328, -0.718399), cameraTarget=(53.0432, -51.284, 
        598.241))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4827.9, 
        farPlane=7923.63, width=5255.98, height=2322.1, cameraPosition=(
        -111.913, 1844.98, 6702.38), cameraUpVector=(-0.290608, 0.752643, 
        -0.590827), cameraTarget=(53.0435, -51.2839, 598.241))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4753.66, 
        farPlane=7997.87, width=5175.16, height=2286.4)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4446.49, 
        farPlane=8318.39, width=4840.75, height=2138.66, cameraPosition=(
        1664.68, 2752.62, 6112.94), cameraUpVector=(-0.348022, 0.689279, 
        -0.635433), cameraTarget=(47.9566, -53.8827, 599.929))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4486.17, 
        farPlane=8278.7, width=4883.96, height=2157.75, cameraPosition=(
        1664.68, 2752.62, 6112.94), cameraUpVector=(-0.209537, 0.700787, 
        -0.681903), cameraTarget=(47.9566, -53.8827, 599.929))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4761.6, 
        farPlane=8033.19, width=5183.83, height=2290.23, cameraPosition=(
        1554.93, 811.828, 6752.61), cameraUpVector=(-0.0390011, 0.886541, 
        -0.461003), cameraTarget=(48.1558, -50.3597, 598.768))
    p = mdb.models['Model-1'].parts['coil']
    p.DatumCsysByThreePoints(name='Datum csys-1', coordSysType=CYLINDRICAL, 
        origin=(0.0, 0.0, 0.0), line1=(1.0, 0.0, 0.0), line2=(0.0, 1.0, 0.0))
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    p = mdb.models['Model-1'].parts['coil']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = regionToolset.Region(cells=cells)
    orientation = mdb.models['Model-1'].parts['coil'].datums[2]
    mdb.models['Model-1'].parts['coil'].MaterialOrientation(region=region, 
        orientationType=SYSTEM, axis=AXIS_1, localCsys=orientation, 
        fieldName='', additionalRotationType=ROTATION_NONE, angle=0.0, 
        additionalRotationField='', stackDirection=STACK_3)
    mdb.models['Model-1'].Material(name='S235')
    mdb.models['Model-1'].materials['S235'].Density(table=((7.8e-09, ), ))
    mdb.models['Model-1'].materials['S235'].Conductivity(type=ORTHOTROPIC, 
        temperatureDependency=ON, table=((17.976, 59.92, 59.92, 0.0), (
        17.6056125, 58.685375, 58.685375, 50.0), (17.1639, 57.213, 57.213, 
        100.0), (16.6605375, 55.535125, 55.535125, 150.0), (16.1052, 53.684, 
        53.684, 200.0), (15.5075625, 51.691875, 51.691875, 250.0), (14.8773, 
        49.591, 49.591, 300.0), (14.2240875, 47.413625, 47.413625, 350.0), (
        13.5576, 45.192, 45.192, 400.0), (12.8875125, 42.958375, 42.958375, 
        450.0), (12.2235, 40.745, 40.745, 500.0), (11.5752375, 38.584125, 
        38.584125, 550.0), (10.9524, 36.508, 36.508, 600.0), (10.3646625, 
        34.548875, 34.548875, 650.0), (9.8217, 32.739, 32.739, 700.0)))
    mdb.models['Model-1'].materials['S235'].SpecificHeat(temperatureDependency=ON, 
        table=((457300000.0, 0.0), (471944601.3, 50.0), (487449123.8, 100.0), (
        503864061.5, 150.0), (521242873.4, 200.0), (539642157.5, 250.0), (
        559121835.3, 300.0), (579745346.7, 350.0), (601579857.0, 400.0), (
        624696475.1, 450.0), (649170485.5, 500.0), (675081593.5, 550.0), (
        702514184.4, 600.0), (731557598.8, 650.0), (762306423.0, 700.0)))
    mdb.models['Model-1'].HomogeneousSolidSection(name='Section-225', 
        material='S235', thickness=None)
    p = mdb.models['Model-1'].parts['coil']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = p.Set(cells=cells, name='Set-2')
    p = mdb.models['Model-1'].parts['coil']
    p.SectionAssignment(region=region, sectionName='Section-225', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)
    a = mdb.models['Model-1'].rootAssembly
    a.DatumCsysByDefault(CARTESIAN)
    p = mdb.models['Model-1'].parts['coil']
    a.Instance(name='coil-1', part=p, dependent=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].HeatTransferStep(name='Step-1', previous='Initial', 
        timePeriod=216000.0, maxNumInc=100000, initialInc=200.0, minInc=5.0, 
        maxInc=1000.0, deltmx=100.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Initial')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON, adaptiveMeshConstraints=OFF)
    a = mdb.models['Model-1'].rootAssembly
    c1 = a.instances['coil-1'].cells
    cells1 = c1.getSequenceFromMask(mask=('[#1 ]', ), )
    f1 = a.instances['coil-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#f ]', ), )
    e1 = a.instances['coil-1'].edges
    edges1 = e1.getSequenceFromMask(mask=('[#f ]', ), )
    v1 = a.instances['coil-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#f ]', ), )
    region = a.Set(vertices=verts1, edges=edges1, faces=faces1, cells=cells1, 
        name='Set-1')
    mdb.models['Model-1'].Temperature(name='Predefined Field-1', 
        createStepName='Initial', region=region, distributionType=UNIFORM, 
        crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(650.0, 
        ))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, interactions=ON, constraints=ON, 
        engineeringFeatures=ON)
    mdb.models['Model-1'].FilmConditionProp(name='IntProp-1', 
        temperatureDependency=ON, dependencies=0, property=((alpha1, 20.0), (
        alpha2, 340.0), (alpha3, 650.0)))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4174.01, 
        farPlane=8614.04, width=4544.11, height=2007.6, cameraPosition=(
        3744.63, 3640.31, 4289.83), cameraUpVector=(-0.396616, 0.552425, 
        -0.733159), cameraTarget=(53.0432, -51.284, 598.241))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4464.65, 
        farPlane=8336.14, width=4860.52, height=2147.39, cameraPosition=(
        3020.47, 2042.62, 5860.7), cameraUpVector=(-0.241231, 0.778898, 
        -0.5789), cameraTarget=(53.0432, -51.284, 598.241))
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['coil-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#f ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-1')
    mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='Step-1', 
        surface=region, definition=PROPERTY_REF, 
        interactionProperty='IntProp-1', sinkTemperature=20.0, 
        sinkAmplitude='', sinkDistributionType=UNIFORM, sinkFieldName='')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4437.66, 
        farPlane=8363.13, width=4831.14, height=2134.41, viewOffsetX=525.211, 
        viewOffsetY=205)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4699.96, 
        farPlane=9039.07, width=5116.7, height=2260.57, cameraPosition=(
        5466.74, 3261.73, 3184.29), cameraUpVector=(-0.466072, 0.588939, 
        -0.660248), cameraTarget=(334.926, 227.893, 872.601), 
        viewOffsetX=556.256, viewOffsetY=217.117)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4442.34, 
        farPlane=8510.99, width=4836.24, height=2136.66, cameraPosition=(
        3079.82, 2094.95, 5905.01), cameraUpVector=(-0.302925, 0.764515, 
        -0.568994), cameraTarget=(-75.5116, -153.182, 818.424), 
        viewOffsetX=525.766, viewOffsetY=205.216)
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['coil-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#d ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-2')
    mdb.models['Model-1'].RadiationToAmbient(name='Int-2', createStepName='Step-1', 
        surface=region, radiationType=AMBIENT, distributionType=UNIFORM, 
        field='', emissivity=0.93, ambientTemperature=20.0, 
        ambientTemperatureAmp='')
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['coil-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#2 ]', ), )
    surf1 = a.Surface(side1Faces=side1Faces1, name='Surf-3')
    surfaces =(surf1, )
    mdb.models['Model-1'].CavityRadiationProp(name='IntProp-2', property=((0.93, ), 
        ))
    props =("IntProp-2", )
    mdb.models['Model-1'].CavityRadiation(name='Int-3', createStepName='Step-1', 
        surfaces=surfaces, surfaceEmissivities=props, ambientTemp=20.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=OFF, 
        constraints=OFF, connectors=OFF, engineeringFeatures=OFF, 
        adaptiveMeshConstraints=ON)
    del mdb.models['Model-1'].fieldOutputRequests['F-Output-1']
    mdb.models['Model-1'].FieldOutputRequest(name='F-Output-1', 
        createStepName='Step-1', variables=('NT', ), numIntervals=6)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=ON, 
        adaptiveMeshConstraints=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p1 = mdb.models['Model-1'].parts['coil']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF, mesh=ON)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=ON)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4319.42, 
        farPlane=8501.62, width=4702.44, height=2084.47, cameraPosition=(
        4260.01, 1832.52, 5026.47), cameraUpVector=(-0.340605, 0.798271, 
        -0.496741), cameraTarget=(49.5815, -49.8217, 597.858))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4813.49, 
        farPlane=8003.81, width=5240.32, height=2322.9, cameraPosition=(
        -1435.2, 658.797, -5611.41), cameraUpVector=(0.367293, 0.859143, 
        0.356328), cameraTarget=(34.9246, -52.8424, 570.481))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4634.35, 
        farPlane=8185.08, width=5045.3, height=2236.45, cameraPosition=(967.98, 
        2151.16, -5360.26), cameraUpVector=(0.556677, 0.527211, 0.641996), 
        cameraTarget=(40.4102, -49.4359, 571.054))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4754.84, 
        farPlane=8125.76, width=5176.48, height=2294.6, cameraPosition=(
        1980.43, -685.377, -5490.11), cameraUpVector=(0.769951, 0.291706, 
        0.567524), cameraTarget=(42.8899, -56.3835, 570.736))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4584.07, 
        farPlane=8233.58, width=4990.57, height=2212.19, cameraPosition=(
        877.113, 2709.84, -5141.37), cameraUpVector=(0.88994, -0.162509, 
        0.426143), cameraTarget=(34.9611, -31.9844, 573.242))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4394.32, 
        farPlane=8444.22, width=4783.99, height=2120.62, cameraPosition=(
        2864.13, 2479.32, -4582.6), cameraUpVector=(0.696085, -0.247768, 
        0.673852), cameraTarget=(39.551, -32.5169, 574.533))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4422.18, 
        farPlane=8416.35, width=4814.33, height=2134.07, cameraPosition=(
        2864.13, 2479.32, -4582.6), cameraUpVector=(0.674956, -0.109312, 
        0.729716), cameraTarget=(39.551, -32.5169, 574.533))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4422.84, 
        farPlane=8415.69, width=4815.06, height=2134.39, cameraPosition=(
        2864.13, 2479.32, -4582.6), cameraUpVector=(0.695246, -0.237455, 
        0.678416), cameraTarget=(39.551, -32.5169, 574.533))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4552.79, 
        farPlane=8308.25, width=4956.54, height=2197.1, cameraPosition=(
        3339.57, 1118.89, -4780.47), cameraUpVector=(0.614099, -0.372255, 
        0.695923), cameraTarget=(41.4202, -37.8656, 573.755))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4535.85, 
        farPlane=8325.2, width=4938.09, height=2188.93, cameraPosition=(
        3339.57, 1118.89, -4780.47), cameraUpVector=(0.620135, -0.341425, 
        0.706301), cameraTarget=(41.4202, -37.8656, 573.755))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4535.44, 
        farPlane=8325.6, width=4937.65, height=2188.73, cameraPosition=(
        3339.57, 1118.89, -4780.47), cameraUpVector=(0.619438, 0.0234275, 
        0.784696), cameraTarget=(41.4202, -37.8656, 573.755))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4640.81, 
        farPlane=8239.49, width=5052.37, height=2239.58, cameraPosition=(
        3952.2, 65.8343, -4484.66), cameraUpVector=(0.541103, -0.0778408, 
        0.837346), cameraTarget=(44.8968, -43.8417, 575.434))
    p = mdb.models['Model-1'].parts['coil']
    c = p.cells
    pickedCells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    v1, e, d1 = p.vertices, p.edges, p.datums
    p.PartitionCellByPlaneThreePoints(cells=pickedCells, point1=p.InterestingPoint(
        edge=e[1], rule=CENTER), point2=p.InterestingPoint(edge=e[1], 
        rule=MIDDLE), point3=p.InterestingPoint(edge=e[0], rule=MIDDLE))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4591.05, 
        farPlane=8301.62, width=4998.19, height=2215.57, cameraPosition=(
        2343.58, -1615.05, -5184.19), cameraUpVector=(0.626406, -0.323096, 
        0.709383), cameraTarget=(33.3758, -55.8803, 570.424))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4421.41, 
        farPlane=8446.92, width=4813.52, height=2133.71, cameraPosition=(
        4295.5, 1339.84, -3999.37), cameraUpVector=(0.482591, -0.204662, 
        0.851598), cameraTarget=(49.2128, -31.9056, 580.037))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4592.88, 
        farPlane=8255.71, width=5000.2, height=2216.46, cameraPosition=(
        2338.17, 1562.24, -5176.34), cameraUpVector=(0.752805, -0.286227, 
        0.592756), cameraTarget=(37.0033, -30.5183, 572.695))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4641.86, 
        farPlane=8206.74, width=4750.31, height=2105.69, viewOffsetX=336.531, 
        viewOffsetY=23.7984)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4457.2, 
        farPlane=8186.06, width=4561.34, height=2021.92, cameraPosition=(
        3826.88, -830.061, -4363.02), cameraUpVector=(0.489622, -0.241192, 
        0.837912), cameraTarget=(-39.9485, -39.8985, 667.583), 
        viewOffsetX=323.144, viewOffsetY=22.8517)
    p = mdb.models['Model-1'].parts['coil']
    e = p.edges
    pickedEdges = e.getSequenceFromMask(mask=('[#10 ]', ), )
    p.seedEdgeByNumber(edges=pickedEdges, number=5, constraint=FINER)
    p = mdb.models['Model-1'].parts['coil']
    p.seedPart(size=160.0, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Model-1'].parts['coil']
    p.generateMesh()
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4513.97, 
        farPlane=8425.69, width=4619.44, height=2047.68, cameraPosition=(
        3556.12, 1875.24, -4471.92), cameraUpVector=(0.612905, -0.145162, 
        0.776708), cameraTarget=(164.384, -81.457, 582.889), 
        viewOffsetX=327.26, viewOffsetY=23.1428)
    elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
    elemType2 = mesh.ElemType(elemCode=DC3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=DC3D4, elemLibrary=STANDARD)
    p = mdb.models['Model-1'].parts['coil']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#3 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    a = mdb.models['Model-1'].rootAssembly
    a.regenerate()
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=OFF)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4470.59, 
        farPlane=8482.74, width=4867, height=2150.25, cameraPosition=(3157.38, 
        1966.1, 5913.85), cameraUpVector=(-0.447964, 0.756994, -0.475698), 
        cameraTarget=(2.04942, -282.036, 827.261), viewOffsetX=529.11, 
        viewOffsetY=206.521)
    mdb.Job(name='Job-1', model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    mdb.jobs['Job-1'].submit(consistencyChecking=OFF)
    session.mdbData.summary()
    o3 = session.openOdb(name='C:/temp/Job-1.odb')
    session.viewports['Viewport: 1'].setValues(displayedObject=o3)
    session.viewports['Viewport: 1'].makeCurrent()
    session.viewports['Viewport: 1'].odbDisplay.display.setValues(plotState=(
        CONTOURS_ON_DEF, ))
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.mdbData.summary()
    session.viewports['Viewport: 1'].setValues(
        displayedObject=session.odbs['C:/temp/Job-1.odb'])
    o3 = session.openOdb(name='C:/temp/Job-1.odb')
    session.viewports['Viewport: 1'].setValues(displayedObject=o3)
    session.viewports['Viewport: 1'].makeCurrent()
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4445.83, 
        farPlane=8319.8, width=5109.69, height=2138.44, cameraPosition=(
        2051.87, 2055.65, 6284.17), cameraUpVector=(-0.308084, 0.774213, 
        -0.552881), cameraTarget=(52.932, -51.2838, 598.351))
    session.viewports['Viewport: 1'].odbDisplay.setFrame(step=0, frame=37 )
    session.viewports['Viewport: 1'].odbDisplay.setFrame(step=0, frame=37 )
	
	
Macro1(0.004,0.003,0.002)

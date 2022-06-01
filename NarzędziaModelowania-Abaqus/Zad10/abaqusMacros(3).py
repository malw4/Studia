# -*- coding: mbcs -*-
# Do not delete the following import lines
from abaqus import *
from abaqusConstants import *
import __main__


def Macro2():
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
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON, mesh=OFF)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=OFF)
    session.viewports['Viewport: 1'].setValues(displayedObject=None)
    mdb.models['Model-1'].Material(name='ABS')
    mdb.models['Model-1'].materials['ABS'].Density(table=((1.05e-09, ), ))
    mdb.models['Model-1'].materials['ABS'].Expansion(table=((9e-05, ), ))
    mdb.models['Model-1'].materials['ABS'].Elastic(temperatureDependency=ON, 
        table=((1829.088875, 0.33, 25.14928785), (1720.912328, 0.33, 
        49.81618708), (1476.127177, 0.33, 75.15000962), (1412.53248, 0.33, 
        80.31782312), (1251.214994, 0.33, 90.12967953), (1124.206044, 0.33, 
        95.28654605), (841.1064864, 0.33, 100.2438408), (509.2327495, 0.33, 
        105.0200895), (201.7551246, 0.33, 109.6279232), (64.98412087, 0.33, 
        114.9557309), (20.91353094, 0.33, 119.781662), (10.98306227, 0.33, 
        124.786113), (5.23289385, 0.33, 149.8159465)))
    mdb.models['Model-1'].materials['ABS'].Plastic(temperatureDependency=ON, 
        table=((24.96551724, 0.0, 25.12194741), (24.96551724, 0.3, 
        25.12194741), (18.27586207, 0.0, 51.92680553), (18.27586207, 0.3, 
        51.92680553), (13.31034483, 0.0, 71.56093727), (13.31034483, 0.3, 
        71.56093727), (7.586206897, 0.0, 94.95116378), (7.586206897, 0.3, 
        94.95116378), (6.965517241, 0.0, 96.14628484), (6.965517241, 0.3, 
        96.14628484), (5.724137931, 0.0, 96.487748), (5.724137931, 0.3, 
        96.487748), (4.482758621, 0.0, 96.4878), (4.482758621, 0.3, 96.4878), (
        3.172413793, 0.0, 96.65847958), (3.172413793, 0.3, 96.65847958), (
        2.344827586, 0.0, 97.51213748), (2.344827586, 0.3, 97.51213748), (
        1.655172414, 0.0, 98.87799013), (1.655172414, 0.3, 98.87799013), (
        1.24137931, 0.0, 100.9267691), (1.24137931, 0.3, 100.9267691), (
        1.172413793, 0.0, 103.6584744), (1.172413793, 0.3, 103.6584744), (
        1.103448276, 0.0, 109.1218849), (1.103448276, 0.3, 109.1218849), (
        1.034482759, 0.0, 149.4145379), (1.034482759, 0.3, 149.4145379)))
    mdb.models['Model-1'].materials['ABS'].SpecificHeat(temperatureDependency=ON, 
        table=((1293814433.0, 19.96238692), (1484536082.0, 50.01695334), (
        1597938144.0, 80.06019465), (1855670103.0, 104.9980782), (2000000000.0, 
        133.9473142), (2097938144.0, 153.7352945), (2237113402.0, 190.0073442), 
        (2340206186.0, 225.1755735), (2371134021.0, 249.7140582)))
    mdb.models['Model-1'].materials['ABS'].Conductivity(temperatureDependency=ON, 
        table=((0.150308008, 20.1338755), (0.154620123, 50.1556252), (
        0.157494867, 67.15477413), (0.160657084, 85.23870637), (0.164394251, 
        102.9593105), (0.168706366, 115.6126391), (0.17301848, 129.7133362), (
        0.179055441, 143.8095753), (0.184804928, 158.9920836), (0.189979466, 
        172.0050254), (0.194579055, 185.3812953), (0.199753593, 198.394237), (
        0.205215606, 213.2156463), (0.209527721, 227.6781855), (0.21613963, 
        249.7334648)))
    mdb.models['Model-1'].Material(name='Epoxy')
    mdb.models['Model-1'].materials['Epoxy'].Density(table=((1.9e-09, ), ))
    mdb.models['Model-1'].materials['Epoxy'].Elastic(table=((20000.0, 0.38), ))
    mdb.models['Model-1'].materials['Epoxy'].Expansion(table=((6e-05, ), ))
    mdb.models['Model-1'].materials['Epoxy'].SpecificHeat(table=((550000000.0, ), 
        ))
    mdb.models['Model-1'].materials['Epoxy'].Conductivity(table=((0.2, ), ))
    mdb.saveAs(pathName='C:/temp/kolokwium')
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=ON)
    s1 = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=200.0)
    g, v, d, c = s1.geometry, s1.vertices, s1.dimensions, s1.constraints
    s1.setPrimaryObject(option=STANDALONE)
    s1.rectangle(point1=(0.0, 0.0), point2=(100.0, 4.0))
    p = mdb.models['Model-1'].Part(name='plate', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['plate']
    p.BaseSolidExtrude(sketch=s1, depth=12.0)
    s1.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['plate']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    mdb.save()
    s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=200.0)
    g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
    s.setPrimaryObject(option=STANDALONE)
    s.rectangle(point1=(-6.0, -6.0), point2=(106.0, 10.0))
    p = mdb.models['Model-1'].Part(name='table', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['table']
    p.BaseSolidExtrude(sketch=s, depth=4.0)
    s.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['table']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    mdb.save()
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    mdb.models['Model-1'].HomogeneousSolidSection(name='Section-ABS', 
        material='ABS', thickness=None)
    mdb.models['Model-1'].HomogeneousSolidSection(name='Section-Epoxy', 
        material='Epoxy', thickness=None)
    mdb.save()
    p1 = mdb.models['Model-1'].parts['plate']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['plate']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = p.Set(cells=cells, name='Set-1')
    p = mdb.models['Model-1'].parts['plate']
    p.SectionAssignment(region=region, sectionName='Section-ABS', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    p1 = mdb.models['Model-1'].parts['table']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['table']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = p.Set(cells=cells, name='Set-1')
    p = mdb.models['Model-1'].parts['table']
    p.SectionAssignment(region=region, sectionName='Section-Epoxy', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    mdb.save()
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    a = mdb.models['Model-1'].rootAssembly
    a.DatumCsysByDefault(CARTESIAN)
    p = mdb.models['Model-1'].parts['plate']
    a.Instance(name='plate-1', part=p, dependent=ON)
    p = mdb.models['Model-1'].parts['table']
    a.Instance(name='table-1', part=p, dependent=ON)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=213.75, 
        farPlane=292.276, width=132.909, height=57.331, cameraPosition=(119.29, 
        -228.707, 83.551), cameraUpVector=(-0.166893, 0.593148, 0.787605), 
        cameraTarget=(54.9201, -0.98564, 4.06567))
    mdb.save()
    a = mdb.models['Model-1'].rootAssembly
    a.translate(instanceList=('table-1', ), vector=(0.0, 0.0, -4.0))
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON)
    a = mdb.models['Model-1'].rootAssembly
    region = a.instances['plate-1'].sets['Set-1']
    mdb.models['Model-1'].Temperature(name='Predefined Field-1', 
        createStepName='Initial', region=region, distributionType=UNIFORM, 
        crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(25.0, 
        ))
    a = mdb.models['Model-1'].rootAssembly
    region = a.instances['table-1'].sets['Set-1']
    mdb.models['Model-1'].Temperature(name='Predefined Field-table', 
        createStepName='Initial', region=region, distributionType=UNIFORM, 
        crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(100.0, 
        ))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, connectors=OFF, adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].HeatTransferStep(name='Step-1', previous='Initial', 
        timePeriod=4500.0, maxNumInc=1000000, initialInc=1.0, minInc=1e-05, 
        maxInc=5.0, deltmx=100.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON, adaptiveMeshConstraints=OFF)
    mdb.models['Model-1'].TabularAmplitude(name='Amp-1', timeSpan=STEP, 
        smooth=SOLVER_DEFAULT, data=((0.0, 1.0), (2200.0, 1.0), (4500.0, 
        0.25)))
    a = mdb.models['Model-1'].rootAssembly
    region = a.instances['table-1'].sets['Set-1']
    mdb.models['Model-1'].TemperatureBC(name='BC-1', createStepName='Step-1', 
        region=region, fixed=OFF, distributionType=UNIFORM, fieldName='', 
        magnitude=100.0, amplitude='Amp-1')
    mdb.models.changeKey(fromName='Model-1', toName='Thermal')
    a = mdb.models['Thermal'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=218.52, 
        farPlane=288.779, width=82.8254, height=35.7271, viewOffsetX=1.48043, 
        viewOffsetY=0.250293)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=195.517, 
        farPlane=322.589, width=74.1065, height=31.9662, cameraPosition=(
        279.314, 122.364, 10.9414), cameraUpVector=(-0.378587, -0.0618865, 
        0.923495), cameraTarget=(59.8724, 3.60933, 3.1289), 
        viewOffsetX=1.32459, viewOffsetY=0.223945)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=193.007, 
        farPlane=323.641, width=73.155, height=31.5557, cameraPosition=(
        -208.285, 1.76682, -0.719511), cameraUpVector=(0.321318, 0.0205214, 
        0.946749), cameraTarget=(41.3303, 2.41731, 2.44163), 
        viewOffsetX=1.30758, viewOffsetY=0.22107)
    a = mdb.models['Thermal'].rootAssembly
    f1 = a.instances['plate-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#1f ]', ), )
    a.Set(faces=faces1, name='Surf_HT_plate')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=189.999, 
        farPlane=326.648, width=104.816, height=45.2129, viewOffsetX=0.795867, 
        viewOffsetY=-0.258924)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=226.625, 
        farPlane=289.734, width=125.022, height=53.9287, cameraPosition=(
        10.0044, 246.981, -67.0371), cameraUpVector=(0.293036, -0.0320276, 
        0.955565), cameraTarget=(49.7623, 9.79585, -0.0975342), 
        viewOffsetX=0.949287, viewOffsetY=-0.308837)
    session.viewports['Viewport: 1'].assemblyDisplay.hideInstances(instances=(
        'table-1', ))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=231.695, 
        farPlane=288.816, width=127.819, height=55.1353, cameraPosition=(
        12.6436, 197.544, -161.67), cameraUpVector=(0.260563, 0.359997, 
        0.895829), cameraTarget=(49.8542, 8.06259, -3.46004), 
        viewOffsetX=0.970524, viewOffsetY=-0.315746)
    a = mdb.models['Thermal'].rootAssembly
    s1 = a.instances['plate-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#20 ]', ), )
    a.Surface(side1Faces=side1Faces1, name='bottom')
    session.viewports['Viewport: 1'].assemblyDisplay.showInstances(instances=(
        'table-1', ))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=208.281, 
        farPlane=309.572, width=114.902, height=49.5637, cameraPosition=(
        -66.3687, 180.505, -143.107), cameraUpVector=(-0.0438847, 0.271887, 
        0.961328), cameraTarget=(46.7544, 7.953, -2.58177), 
        viewOffsetX=0.872449, viewOffsetY=-0.283839)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=203.512, 
        farPlane=315.321, width=112.271, height=48.4289, cameraPosition=(
        -106.839, -196.292, 62.1705), cameraUpVector=(-0.228788, 0.790461, 
        0.568179), cameraTarget=(43.626, -5.74363, 4.11808), 
        viewOffsetX=0.852473, viewOffsetY=-0.27734)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=203.837, 
        farPlane=314.996, width=112.45, height=48.5063, cameraPosition=(
        -106.859, -196.113, 62.7066), cameraUpVector=(0.119901, 0.586141, 
        0.801288), cameraTarget=(43.6064, -5.56485, 4.65419), 
        viewOffsetX=0.853835, viewOffsetY=-0.277783)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=203.815, 
        farPlane=315.019, width=112.438, height=48.5011, cameraPosition=(
        -106.862, -196.116, 62.6911), cameraUpVector=(0.109499, 0.593219, 
        0.79756), cameraTarget=(43.6039, -5.56757, 4.63872), 
        viewOffsetX=0.853743, viewOffsetY=-0.277753)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=226.989, 
        farPlane=292.625, width=125.222, height=54.0156, cameraPosition=(
        91.8534, -244.97, 72.9652), cameraUpVector=(-0.0771988, 0.571324, 
        0.817086), cameraTarget=(50.9171, -8.17271, 5.36425), 
        viewOffsetX=0.950813, viewOffsetY=-0.309333)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, interactions=ON, constraints=ON, 
        engineeringFeatures=ON)
    a = mdb.models['Thermal'].rootAssembly
    s1 = a.instances['table-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#10 ]', ), )
    region1=a.Surface(side1Faces=side1Faces1, name='m_Surf-2')
    a = mdb.models['Thermal'].rootAssembly
    region2=a.surfaces['bottom']
    mdb.models['Thermal'].Tie(name='Constraint-1', master=region1, slave=region2, 
        positionToleranceMethod=COMPUTED, adjust=ON, tieRotations=ON, 
        thickness=ON)
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=ON, 
        interactions=OFF, constraints=OFF, connectors=OFF, 
        engineeringFeatures=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p = mdb.models['Thermal'].parts['table']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF, mesh=ON)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p = mdb.models['Thermal'].parts['table']
    p.seedPart(size=4.5, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Thermal'].parts['table']
    p.generateMesh()
    elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
    elemType2 = mesh.ElemType(elemCode=DC3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=DC3D4, elemLibrary=STANDARD)
    p = mdb.models['Thermal'].parts['table']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    p = mdb.models['Thermal'].parts['plate']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    p = mdb.models['Thermal'].parts['plate']
    p.seedPart(size=2.5, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Thermal'].parts['plate']
    p.generateMesh()
    elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
    elemType2 = mesh.ElemType(elemCode=DC3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=DC3D4, elemLibrary=STANDARD)
    p = mdb.models['Thermal'].parts['plate']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    a = mdb.models['Thermal'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    a1 = mdb.models['Thermal'].rootAssembly
    a1.regenerate()
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=OFF)
    mdb.Job(name='Thermal', model='Thermal', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    mdb.Model(name='Structural', objectToCopy=mdb.models['Thermal'])
    a = mdb.models['Structural'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=ON)
    mdb.models['Structural'].StaticStep(name='Step-1', previous='Initial', 
        maintainAttributes=True, timePeriod=4500.0, maxNumInc=1000000, 
        initialInc=5.0, minInc=1e-05, maxInc=10.0, nlgeom=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=OFF)
    mdb.Job(name='Structural', model='Structural', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    import sys
    sys.path.insert(8, 
        r'c:/SIMULIA/CAE/2020SE/win_b64/code/python2.7/lib/abaqus_plugins/AMModeler')
    from abaqus import *
    from amConstants import *
    import customKernel, amModule, amKernelInit
    amModule.createAMModel(amModelName='AM-Model-1', modelName1='Thermal', 
        stepName1='Step-1', analysisType1=HEAT_TRANSFER, isSequential=ON, 
        modelName2='Structural', stepName2='Step-1', 
        analysisType2=STATIC_GENERAL, processType=AMPROC_ABAQUS_BUILTIN)
    mdb.customData.am.amModels['AM-Model-1'].addEventSeries(
        eventSeriesName='MaterialPath', 
        eventSeriesTypeName='"ABQ_AM.MaterialDeposition"', 
        timeSpan='TOTAL TIME', fileName='C:/temp/path2.txt', isFile=ON)
    mdb.customData.am.amModels['AM-Model-1'].addEventSeries(
        eventSeriesName='HeatPath', 
        eventSeriesTypeName='"ABQ_AM.PowerMagnitude"', timeSpan='TOTAL TIME', 
        fileName='C:/temp/path2.txt', isFile=ON)
    mdb.customData.am.amModels['AM-Model-1'].addTableCollection(
        tableCollectionName='ABQ_AM_Material')
    mdb.customData.am.amModels['AM-Model-1'].dataSetup.tableCollections['ABQ_AM_Material'].ParameterTable(
        name='_parameterTable_"ABQ_AM.MaterialDeposition.Bead"_', 
        parameterTabletype='"ABQ_AM.MaterialDeposition.Bead"', parameterData=((
        'Z', 0.2, 0.4, 0, 'Below'), ))
    mdb.customData.am.amModels['AM-Model-1'].dataSetup.tableCollections['ABQ_AM_Material'].ParameterTable(
        name='_parameterTable_"ABQ_AM.MaterialDeposition"_', 
        parameterTabletype='"ABQ_AM.MaterialDeposition"', parameterData=((
        'MaterialPath', 'Bead'), ))
    mdb.customData.am.amModels['AM-Model-1'].addTableCollection(
        tableCollectionName='ABQ_AM_Heat')
    mdb.customData.am.amModels['AM-Model-1'].dataSetup.tableCollections['ABQ_AM_Heat'].PropertyTable(
        name='_propertyTable_"ABQ_AM.AbsorptionCoeff"_', 
        propertyTableType='"ABQ_AM.AbsorptionCoeff"', propertyTableData=((1, ), 
        ), numDependencies=0, temperatureDependency=OFF)
    mdb.customData.am.amModels['AM-Model-1'].dataSetup.tableCollections['ABQ_AM_Heat'].ParameterTable(
        name='_parameterTable_"ABQ_AM.MovingHeatSource"_', 
        parameterTabletype='"ABQ_AM.MovingHeatSource"', parameterData=((
        'HeatPath', 'Concentrated'), ))
    a = mdb.models['Thermal'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    mdb.customData.am.amModels['AM-Model-1'].assignAMPart(amPartsData=(('plate-1', 
        'Build Part'), ('table-1', 'Unassigned'), ('', ''), ('', ''), ('', 
        '')))
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON)
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    mdb.customData.am.amModels['AM-Model-1'].addMaterialArrival(
        materialArrivalName='Material Source -1', 
        tableCollection='ABQ_AM_Material', followDeformation=OFF, 
        useElementSet=OFF, elementSetRegion=())
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    mdb.customData.am.amModels['AM-Model-1'].addHeatSourceDefinition(
        heatSourceName='Heat Source -1', 
        dfluxDistribution='Moving-UserDefined', dfluxMagnitude=1, 
        tableCollection='ABQ_AM_Heat', useElementSet=OFF, elementSetRegion=())
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    highlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    mdb.customData.am.amModels['AM-Model-1'].addCoolingInteractions(
        coolingInteractionName='Cooling Interaction -1', useElementSet=ON, 
        elementSetRegion=('Surf_HT_plate', ), isConvectionActive=ON, 
        isRadiationActive=ON, filmDefinition='Embedded Coefficient', 
        filmCoefficient=0.008, filmcoefficeintamplitude='Instantaneous', 
        sinkDefinition='Uniform', sinkTemperature=25, 
        sinkAmplitude='Instantaneous', radiationType='toAmbient', 
        emissivityDistribution='Uniform', emissivity=0.92, 
        ambientTemperature=25, ambientTemperatureAmplitude='Instanteneous')
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['plate-1'])
    unhighlight(mdb.models['Thermal'].rootAssembly.instances['table-1'])
    mdb.save()
    a = mdb.models['Structural'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Initial')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=210.424, 
        farPlane=298.025, width=133.565, height=57.6138, cameraPosition=(
        133.666, -210.669, 115.482), cameraUpVector=(0.113378, 0.776665, 
        0.619627), cameraTarget=(54.9332, -1.14946, 2.21631))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=223.051, 
        farPlane=289.937, width=141.58, height=61.0711, cameraPosition=(
        81.9922, -221.135, -118.465), cameraUpVector=(0.00137524, -0.148375, 
        0.98893), cameraTarget=(54.2476, -1.28832, -0.887751))
    a = mdb.models['Structural'].rootAssembly
    f1 = a.instances['table-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#20 ]', ), )
    region = a.Set(faces=faces1, name='Set-3')
    mdb.models['Structural'].EncastreBC(name='BC-2', createStepName='Initial', 
        region=region, localCsys=None)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    a = mdb.models['Structural'].rootAssembly
    c1 = a.instances['plate-1'].cells
    cells1 = c1.getSequenceFromMask(mask=('[#1 ]', ), )
    f1 = a.instances['plate-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#3f ]', ), )
    e1 = a.instances['plate-1'].edges
    edges1 = e1.getSequenceFromMask(mask=('[#fff ]', ), )
    v1 = a.instances['plate-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#ff ]', ), )
    c2 = a.instances['table-1'].cells
    cells2 = c2.getSequenceFromMask(mask=('[#1 ]', ), )
    f2 = a.instances['table-1'].faces
    faces2 = f2.getSequenceFromMask(mask=('[#3f ]', ), )
    e2 = a.instances['table-1'].edges
    edges2 = e2.getSequenceFromMask(mask=('[#fff ]', ), )
    v2 = a.instances['table-1'].vertices
    verts2 = v2.getSequenceFromMask(mask=('[#ff ]', ), )
    region = a.Set(vertices=verts1+verts2, edges=edges1+edges2, faces=faces1+\
        faces2, cells=cells1+cells2, name='Set-4')
    mdb.models['Structural'].Temperature(name='Predefined Field-3', 
        createStepName='Step-1', distributionType=FROM_FILE, 
        fileName='Thermal', beginStep=1, beginIncrement=None, endStep=None, 
        endIncrement=None, interpolate=ON, absoluteExteriorTolerance=0.0, 
        exteriorTolerance=0.05)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, connectors=OFF, adaptiveMeshConstraints=ON)
    mdb.models['Structural'].StaticStep(name='Step-2', previous='Step-1', 
        timePeriod=1e-05, maxNumInc=1000000, initialInc=1e-05, minInc=1e-10, 
        maxInc=1e-05)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-2')
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=ON, 
        adaptiveMeshConstraints=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=ON)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=224.795, 
        farPlane=284.67, width=142.687, height=61.7477, cameraPosition=(
        69.0241, -249.303, 41.2982), cameraUpVector=(0.278355, 0.484568, 
        0.829284), cameraTarget=(53.9623, -1.908, 2.62687))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=224.575, 
        farPlane=284.889, width=142.548, height=61.6874, cameraPosition=(
        69.0241, -249.303, 41.2982), cameraUpVector=(-0.0456027, 0.472773, 
        0.880003), cameraTarget=(53.9623, -1.908, 2.62687))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=221.444, 
        farPlane=285.504, width=140.56, height=60.8273, cameraPosition=(
        67.9752, -159.9, 198.243), cameraUpVector=(-0.0133692, 0.93929, 
        0.342863), cameraTarget=(53.9463, -0.546175, 5.01753))
    session.viewports['Viewport: 1'].assemblyDisplay.hideInstances(instances=(
        'plate-1', ))
    a = mdb.models['Structural'].rootAssembly
    e1 = a.instances['table-1'].elements
    elements1 = e1.getSequenceFromMask(mask=('[#fff00000 #ffffffff:2 #f ]', ), )
    a.Set(elements=elements1, name='remove')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF, 
        interactions=ON, constraints=ON, connectors=ON, engineeringFeatures=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=OFF)
    a = mdb.models['Structural'].rootAssembly
    region =a.sets['remove']
    mdb.models['Structural'].ModelChange(name='Int-1', createStepName='Step-2', 
        region=region, regionType=ELEMENTS, activeInStep=False, 
        includeStrain=False)
    session.viewports['Viewport: 1'].assemblyDisplay.showInstances(instances=(
        'plate-1', ))
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=ON, 
        interactions=OFF, constraints=OFF, connectors=OFF, 
        engineeringFeatures=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p = mdb.models['Structural'].parts['plate']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    elemType1 = mesh.ElemType(elemCode=C3D8R, elemLibrary=STANDARD, 
        kinematicSplit=AVERAGE_STRAIN, secondOrderAccuracy=OFF, 
        hourglassControl=DEFAULT, distortionControl=DEFAULT)
    elemType2 = mesh.ElemType(elemCode=C3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=C3D4, elemLibrary=STANDARD)
    p = mdb.models['Structural'].parts['plate']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    p = mdb.models['Structural'].parts['table']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    elemType1 = mesh.ElemType(elemCode=C3D8R, elemLibrary=STANDARD, 
        kinematicSplit=AVERAGE_STRAIN, secondOrderAccuracy=OFF, 
        hourglassControl=DEFAULT, distortionControl=DEFAULT)
    elemType2 = mesh.ElemType(elemCode=C3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=C3D4, elemLibrary=STANDARD)
    p = mdb.models['Structural'].parts['table']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    mdb.save()
    a = mdb.models['Structural'].rootAssembly
    a.regenerate()
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(mesh=OFF)
    session.viewports['Viewport: 1'].assemblyDisplay.meshOptions.setValues(
        meshTechnique=OFF)
    mdb.jobs['Structural'].submit(consistencyChecking=OFF)
    session.mdbData.summary()
    o3 = session.openOdb(name='C:/temp/Structural.odb')
    session.viewports['Viewport: 1'].setValues(displayedObject=o3)
    session.viewports['Viewport: 1'].makeCurrent()
    session.viewports['Viewport: 1'].odbDisplay.display.setValues(plotState=(
        CONTOURS_ON_DEF, ))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=213.985, 
        farPlane=290.729, width=135.825, height=58.5889, cameraPosition=(
        106.214, -151.456, 196.388), cameraUpVector=(0.288399, 0.932963, 
        0.215422), cameraTarget=(54.935, -1.14404, 2.21539))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=213.147, 
        farPlane=291.567, width=135.293, height=58.3595, cameraPosition=(
        106.214, -151.456, 196.388), cameraUpVector=(-0.044825, 0.948009, 
        0.315071), cameraTarget=(54.935, -1.14404, 2.21539))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=219.64, 
        farPlane=285.817, width=139.414, height=60.1372, cameraPosition=(
        78.0412, -198.071, 155.966), cameraUpVector=(-0.260202, 0.808164, 
        0.528361), cameraTarget=(54.7669, -1.42223, 1.97417))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=218.974, 
        farPlane=291.184, width=138.991, height=59.9547, cameraPosition=(
        100.252, -246.659, 31.1753), cameraUpVector=(-0.231507, 0.407318, 
        0.883457), cameraTarget=(54.932, -1.78331, 1.0468))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=219.026, 
        farPlane=291.131, width=139.024, height=59.9688, cameraPosition=(
        100.252, -246.659, 31.1753), cameraUpVector=(-0.0429393, 0.443658, 
        0.895167), cameraTarget=(54.932, -1.78331, 1.0468))


Macro2()
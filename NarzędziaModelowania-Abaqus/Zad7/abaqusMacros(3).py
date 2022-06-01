# -*- coding: mbcs -*-
# Do not delete the following import lines
from abaqus import *
from abaqusConstants import *
import __main__

def cuboid(alpha):
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
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=ON)
    s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=200.0)
    g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
    s.setPrimaryObject(option=STANDALONE)
    s.rectangle(point1=(0.0, 0.0), point2=(100.0, 200.0))
    p = mdb.models['Model-1'].Part(name='Part-1', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['Part-1']
    p.BaseSolidExtrude(sketch=s, depth=500.0)
    s.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['Part-1']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    mdb.models['Model-1'].Material(name='Material-1')
    mdb.models['Model-1'].materials['Material-1'].Density(table=((5e-09, ), ))
    mdb.models['Model-1'].materials['Material-1'].SpecificHeat(table=((600000000.0, 
        ), ))
    mdb.models['Model-1'].materials['Material-1'].Conductivity(table=((100.0, ), ))
    mdb.models['Model-1'].HomogeneousSolidSection(name='Section-1', 
     material='Material-1', thickness=None)
    p = mdb.models['Model-1'].parts['Part-1']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = p.Set(cells=cells, name='Set-1')
    p = mdb.models['Model-1'].parts['Part-1']
    p.SectionAssignment(region=region, sectionName='Section-1', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)
    a = mdb.models['Model-1'].rootAssembly
    a.DatumCsysByDefault(CARTESIAN)
    p = mdb.models['Model-1'].parts['Part-1']
    a.Instance(name='Part-1-1', part=p, dependent=ON)
    mdb.saveAs(pathName='C:/temp/kolokwium_zad2')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].HeatTransferStep(name='Step-1', previous='Initial', 
        timePeriod=600.0, maxNumInc=100000, initialInc=10.0, minInc=5.0, 
        maxInc=20.0, deltmx=100.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Initial')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON, adaptiveMeshConstraints=OFF)
    a = mdb.models['Model-1'].rootAssembly
    c1 = a.instances['Part-1-1'].cells
    cells1 = c1.getSequenceFromMask(mask=('[#1 ]', ), )
    f1 = a.instances['Part-1-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#3f ]', ), )
    e1 = a.instances['Part-1-1'].edges
    edges1 = e1.getSequenceFromMask(mask=('[#fff ]', ), )
    v1 = a.instances['Part-1-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#ff ]', ), )
    region = a.Set(vertices=verts1, edges=edges1, faces=faces1, cells=cells1, 
        name='Set-1')
    mdb.models['Model-1'].Temperature(name='Predefined Field-1', 
        createStepName='Initial', region=region, distributionType=UNIFORM, 
        crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(200.0, 
        ))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, interactions=ON, constraints=ON, 
        engineeringFeatures=ON)
    mdb.models['Model-1'].FilmConditionProp(name='IntProp-1', 
        temperatureDependency=OFF, dependencies=0, property=((alpha, ), ))
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=959.649, 
        farPlane=1469.03, width=873.951, height=343.694, cameraPosition=(
        -620.65, -911.508, 296.265), cameraUpVector=(-0.598746, 0.799826, 
        0.0422041), cameraTarget=(42.9308, 85.98, 271.09))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=802.342, 
        farPlane=1596.97, width=730.691, height=287.355, cameraPosition=(
        -384.411, -654.655, -575.33), cameraUpVector=(-0.727242, 0.61453, 
        0.305732), cameraTarget=(46.0485, 89.3697, 259.587))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=882.842, 
        farPlane=1497.42, width=804.003, height=316.186, cameraPosition=(
        1060.07, 223.116, -367.356), cameraUpVector=(-0.449304, 0.887816, 
        0.0995401), cameraTarget=(47.662, 90.3502, 259.819))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=814.138, 
        farPlane=1575.17, width=741.435, height=291.58, cameraPosition=(
        738.606, 415.234, 1173.99), cameraUpVector=(-0.525278, 0.788876, 
        -0.318995), cameraTarget=(49.8709, 89.03, 249.227))
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['Part-1-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#3f ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-1')
    mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='Step-1', 
        surface=region, definition=PROPERTY_REF, 
        interactionProperty='IntProp-1', sinkTemperature=20.0, 
        sinkAmplitude='', sinkDistributionType=UNIFORM, sinkFieldName='')
    session.viewports['Viewport: 1'].view.setValues(nearPlane=851.605, 
        farPlane=1547.2, width=775.557, height=305, cameraPosition=(896.339, 
        -144.816, 1063.9), cameraUpVector=(-0.326181, -0.856909, -0.39914), 
        cameraTarget=(49.3882, 90.7443, 249.564))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=805.515, 
        farPlane=1603.91, width=733.583, height=288.493, cameraPosition=(
        -249.902, -433.132, -787.892), cameraUpVector=(-0.620309, -0.309491, 
        0.720717), cameraTarget=(48.3484, 90.4827, 247.884))
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['Part-1-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#3f ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-2')
    mdb.models['Model-1'].RadiationToAmbient(name='Int-2', createStepName='Step-1', 
        surface=region, radiationType=AMBIENT, distributionType=UNIFORM, 
        field='', emissivity=0.9, ambientTemperature=20.0, 
        ambientTemperatureAmp='')
    mdb.save()
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=OFF, 
        constraints=OFF, connectors=OFF, engineeringFeatures=OFF, 
        adaptiveMeshConstraints=ON)
    del mdb.models['Model-1'].fieldOutputRequests['F-Output-1']
    mdb.models['Model-1'].FieldOutputRequest(name='F-Output-1', 
        createStepName='Step-1', variables=('NT', ), numIntervals=6)
    mdb.save()
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF, mesh=ON)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p1 = mdb.models['Model-1'].parts['Part-1']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['Part-1']
    p.seedPart(size=25.0, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Model-1'].parts['Part-1']
    p.generateMesh()
    elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
    elemType2 = mesh.ElemType(elemCode=DC3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=DC3D4, elemLibrary=STANDARD)
    p = mdb.models['Model-1'].parts['Part-1']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    pickedRegions =(cells, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, elemType2, 
        elemType3))
    a = mdb.models['Model-1'].rootAssembly
    a.regenerate()
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=OFF)
    mdb.Job(name='kolokwium', model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    mdb.jobs['kolokwium'].submit(consistencyChecking=OFF)
    mdb.save()


cuboid(0.1)


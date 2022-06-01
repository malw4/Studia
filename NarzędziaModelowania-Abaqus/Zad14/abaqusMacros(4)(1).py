# -*- coding: mbcs -*-
# Do not delete the following import lines
from abaqus import *
from abaqusConstants import *
import __main__

def Macro1(P, robota):
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
    session.viewports['Viewport: 1'].setValues(displayedObject=None)
    s1 = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=5000.0)
    g, v, d, c = s1.geometry, s1.vertices, s1.dimensions, s1.constraints
    s1.setPrimaryObject(option=STANDALONE)
    s1.Line(point1=(0.0, 0.0), point2=(5000.0, 0.0))
    s1.HorizontalConstraint(entity=g[2], addUndoState=False)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=2775.3, 
        farPlane=6652.79, width=15154.6, height=6644.05, cameraPosition=(
        -1247.08, 770.955, 4714.05), cameraTarget=(-1247.08, 770.955, 0))
    session.viewports['Viewport: 1'].view.setValues(cameraPosition=(3210.17, 
        -104.725, 4714.05), cameraTarget=(3210.17, -104.725, 0))
    s1.ObliqueDimension(vertex1=v[0], vertex2=v[1], textPoint=(2555.51220703125, 
        645.858032226563), value=5000.0)
    p = mdb.models['Model-1'].Part(name='Belka', dimensionality=TWO_D_PLANAR, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['Belka']
    p.BaseWire(sketch=s1)
    s1.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['Belka']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    p = mdb.models['Model-1'].parts['Belka']
    e = p.edges
    pickedEdges = e.getSequenceFromMask(mask=('[#1 ]', ), )
    p.PartitionEdgeByParam(edges=pickedEdges, parameter=0.5)
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    mdb.models['Model-1'].Material(name='Material-1')
    mdb.models['Model-1'].materials['Material-1'].Elastic(table=((200000.0, 0.3), 
        ))
    mdb.models['Model-1'].materials['Material-1'].Plastic(table=((200.0, 0.0), 
        (300.0, 0.1)))
    mdb.models['Model-1'].IProfile(name='Profile-2', l=120.0, h=160.0, b1=120.0, 
        b2=120.0, t1=20.0, t2=20.0, t3=20.0)
    mdb.models['Model-1'].BeamSection(name='Section-1', 
        integration=DURING_ANALYSIS, poissonRatio=0.3, profile='Profile-2', 
        material='Material-1', temperatureVar=LINEAR, 
        consistentMassMatrix=False)
    p = mdb.models['Model-1'].parts['Belka']
    e = p.edges
    edges = e.getSequenceFromMask(mask=('[#3 ]', ), )
    region = regionToolset.Region(edges=edges)
    p = mdb.models['Model-1'].parts['Belka']
    p.SectionAssignment(region=region, sectionName='Section-1', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    p = mdb.models['Model-1'].parts['Belka']
    e = p.edges
    edges = e.getSequenceFromMask(mask=('[#3 ]', ), )
    region=regionToolset.Region(edges=edges)
    p = mdb.models['Model-1'].parts['Belka']
    p.assignBeamSectionOrientation(region=region, method=N1_COSINES, n1=(0.0, 0.0, 
        -1.0))
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, connectors=OFF, adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].StaticStep(name='Step-1', previous='Initial', 
        maxNumInc=1000, initialInc=0.1, nlgeom=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        adaptiveMeshConstraints=OFF)
    a1 = mdb.models['Model-1'].rootAssembly
    a1.DatumCsysByDefault(CARTESIAN)
    p = mdb.models['Model-1'].parts['Belka']
    a1.Instance(name='Belka-1', part=p, dependent=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Initial')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['Belka-1'].edges
    side1Edges1 = s1.getSequenceFromMask(mask=('[#3 ]', ), )
    region = regionToolset.Region(side1Edges=side1Edges1)
    mdb.models['Model-1'].Pressure(name='Load-1', createStepName='Step-1', 
        region=region, distributionType=UNIFORM, field='', magnitude=2.0, 
        amplitude=UNSET)
    a = mdb.models['Model-1'].rootAssembly
    v1 = a.instances['Belka-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#2 ]', ), )
    region = regionToolset.Region(vertices=verts1)
    mdb.models['Model-1'].ConcentratedForce(name='Load-2', createStepName='Step-1', 
        region=region, cf2=(-1)*P, distributionType=UNIFORM, field='', 
        localCsys=None)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Initial')
    a = mdb.models['Model-1'].rootAssembly
    v1 = a.instances['Belka-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#4 ]', ), )
    region = regionToolset.Region(vertices=verts1)
    mdb.models['Model-1'].DisplacementBC(name='BC-1', createStepName='Initial', 
        region=region, u1=SET, u2=SET, ur3=UNSET, amplitude=UNSET, 
        distributionType=UNIFORM, fieldName='', localCsys=None)
    a = mdb.models['Model-1'].rootAssembly
    v1 = a.instances['Belka-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#1 ]', ), )
    region = regionToolset.Region(vertices=verts1)
    mdb.models['Model-1'].DisplacementBC(name='BC-2', createStepName='Initial', 
        region=region, u1=UNSET, u2=SET, ur3=UNSET, amplitude=UNSET, 
        distributionType=UNIFORM, fieldName='', localCsys=None)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF, mesh=ON)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p1 = mdb.models['Model-1'].parts['Belka']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['Belka']
    p.seedPart(size=6.0, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Model-1'].parts['Belka']
    p.generateMesh()
    elemType1 = mesh.ElemType(elemCode=B21, elemLibrary=STANDARD)
    p = mdb.models['Model-1'].parts['Belka']
    e = p.edges
    edges = e.getSequenceFromMask(mask=('[#3 ]', ), )
    pickedRegions =(edges, )
    p.setElementType(regions=pickedRegions, elemTypes=(elemType1, ))
    a = mdb.models['Model-1'].rootAssembly
    a.regenerate()
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, connectors=OFF)
    
    mdb.Job(name=robota, model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    
    mdb.jobs[robota].writeInput(consistencyChecking=OFF)
    mdb.jobs[robota].submit(consistencyChecking=OFF)
    mdb.jobs[robota].waitForCompletion()


    Macro1(10000, 'Job-10')
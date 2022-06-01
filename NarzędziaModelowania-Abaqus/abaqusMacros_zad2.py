# -*- coding: mbcs -*-
# Do not delete the following import lines
from abaqus import *
from abaqusConstants import *
import __main__

def cube(alpha):
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
    s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=200.0)
    g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
    s.setPrimaryObject(option=STANDALONE)
    s.rectangle(point1=(0.0, 0.0), point2=(33.75, 27.5))
    s.ObliqueDimension(vertex1=v[3], vertex2=v[0], textPoint=(18.9667358398438, 
        -18.6345748901367), value=100.0)
    s.ObliqueDimension(vertex1=v[2], vertex2=v[3], textPoint=(50.4405136108398, 
        15.0589408874512), value=100.0)
    p = mdb.models['Model-1'].Part(name='cube', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['cube']
    p.BaseSolidExtrude(sketch=s, depth=100.0)
    s.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['cube']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    mdb.models['Model-1'].Material(name='Material-1')
    mdb.models['Model-1'].materials['Material-1'].Density(table=((7.9e-09, ), ))
    mdb.models['Model-1'].materials['Material-1'].Conductivity(table=((50.0, ), ))
    mdb.models['Model-1'].materials['Material-1'].SpecificHeat(table=((500000000.0, 
        ), ))
    mdb.models['Model-1'].HomogeneousSolidSection(name='Section-1', 
        material='Material-1', thickness=None)
    p = mdb.models['Model-1'].parts['cube']
    c = p.cells
    cells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    region = p.Set(cells=cells, name='Set-1')
    p = mdb.models['Model-1'].parts['cube']
    p.SectionAssignment(region=region, sectionName='Section-1', offset=0.0, 
        offsetType=MIDDLE_SURFACE, offsetField='', 
        thicknessAssignment=FROM_SECTION)
    a = mdb.models['Model-1'].rootAssembly
    session.viewports['Viewport: 1'].setValues(displayedObject=a)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(
        optimizationTasks=OFF, geometricRestrictions=OFF, stopConditions=OFF)
    a = mdb.models['Model-1'].rootAssembly
    a.DatumCsysByDefault(CARTESIAN)
    p = mdb.models['Model-1'].parts['cube']
    a.Instance(name='cube-1', part=p, dependent=ON)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON)
    a = mdb.models['Model-1'].rootAssembly
    c1 = a.instances['cube-1'].cells
    cells1 = c1.getSequenceFromMask(mask=('[#1 ]', ), )
    f1 = a.instances['cube-1'].faces
    faces1 = f1.getSequenceFromMask(mask=('[#3f ]', ), )
    e1 = a.instances['cube-1'].edges
    edges1 = e1.getSequenceFromMask(mask=('[#fff ]', ), )
    v1 = a.instances['cube-1'].vertices
    verts1 = v1.getSequenceFromMask(mask=('[#ff ]', ), )
    region = a.Set(vertices=verts1, edges=edges1, faces=faces1, cells=cells1, 
        name='Set-1')
    mdb.models['Model-1'].Temperature(name='Predefined Field-1', 
        createStepName='Initial', region=region, distributionType=UNIFORM, 
        crossSectionDistribution=CONSTANT_THROUGH_THICKNESS, magnitudes=(200.0, 
        ))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=OFF, bcs=OFF, 
        predefinedFields=OFF, connectors=OFF, adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].HeatTransferStep(name='Step-1', previous='Initial', 
        timePeriod=500.0, maxNumInc=1000, initialInc=5.0, minInc=1.0, 
        maxInc=20.0, deltmx=100.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=ON, 
        constraints=ON, connectors=ON, engineeringFeatures=ON, 
        adaptiveMeshConstraints=OFF)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=273.374, 
        farPlane=543.822, width=308.194, height=128.284, cameraPosition=(
        221.752, 209.208, 288.002))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=284.254, 
        farPlane=528.198, width=320.461, height=133.39, cameraPosition=(
        140.021, 103.701, -303.12), cameraUpVector=(-0.816883, 0.531533, 
        0.223998), cameraTarget=(-14.1521, -26.6958, 52.0979))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=282.128, 
        farPlane=529.857, width=318.064, height=132.392, cameraPosition=(
        -324.967, -270.449, -39.8094), cameraUpVector=(-0.246563, 0.583911, 
        0.773469), cameraTarget=(-11.4378, -24.5118, 50.5609))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=280.87, 
        farPlane=526.596, width=316.645, height=131.802, cameraPosition=(
        73.5991, 299.524, -176.37), cameraUpVector=(-0.942888, -0.284287, 
        -0.17362), cameraTarget=(-13.9958, -28.1699, 51.4373))
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['cube-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#3f ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-1')
    mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='Step-1', 
        surface=region, definition=EMBEDDED_COEFF, filmCoeff=alpha,
        filmCoeffAmplitude='', sinkTemperature=20.0, sinkAmplitude='', 
        sinkDistributionType=UNIFORM, sinkFieldName='')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=OFF, 
        constraints=OFF, connectors=OFF, engineeringFeatures=OFF, 
        adaptiveMeshConstraints=ON)
    del mdb.models['Model-1'].fieldOutputRequests['F-Output-1']
    mdb.models['Model-1'].FieldOutputRequest(name='F-Output-1', 
        createStepName='Step-1', variables=('NT', ), numIntervals=5)
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=OFF, 
        engineeringFeatures=OFF, mesh=ON)
    session.viewports['Viewport: 1'].partDisplay.meshOptions.setValues(
        meshTechnique=ON)
    p1 = mdb.models['Model-1'].parts['cube']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['cube']
    p.seedPart(size=12.0, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Model-1'].parts['cube']
    p.generateMesh()
    elemType1 = mesh.ElemType(elemCode=DC3D8, elemLibrary=STANDARD)
    elemType2 = mesh.ElemType(elemCode=DC3D6, elemLibrary=STANDARD)
    elemType3 = mesh.ElemType(elemCode=DC3D4, elemLibrary=STANDARD)
    p = mdb.models['Model-1'].parts['cube']
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
    mdb.Job(name='Job-1', model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    mdb.jobs['wyn'].writeInput(consistencyChecking=OFF)
    mdb.jobs['wyn'].submit()
    mdb.jobs['wyn'].waitForCompletion()

#cube(0.2)




from abaqus import *
from abaqusConstants import *
from odbAccess import *
from odbSection import *
from sys import argv, exit
#import _main_


def	dataT ():
    odbName='C:/temp/wyn.odb'
    odb = session.openOdb(name=odbName)
    session.viewports['Viewport: 1'].setValues(displayedObject=odb)

    vps = session.viewports[session.currentViewportName]
    #odbName = vps.displayedObject.name
    currentstepnumber = vps.odbDisplay.fieldFrame[0]
    currentstepname = session.odbs[odbName].steps.keys()[currentstepnumber]
    currentframe = vps.odbDisplay.fieldFrame[1]
    currentsteptime = session.odbs[odbName].steps[currentstepname].frames[currentframe].frameValue

    assembly = odb.rootAssembly
    instanceList = assembly.instances.keys()
    instanceName=instanceList[0]

    node=365
    node=node-1
    thePointList= []
    TemperatureList=[]

    #Coordinates from node
    coordsX=assembly.instances[instanceName].nodes[node].coordinates[0]
    coordsY=assembly.instances[instanceName].nodes[node].coordinates[1]
    coordsZ=assembly.instances[instanceName].nodes[node].coordinates[2]
    coords = (coordsX, coordsY, coordsZ)
    thePointList.extend([coords])

    #for Name in odb.rootAssembly.instances.keys():
    #print Name

    for licznik in range (1, currentframe+1):
        TemperaturaXYData=session.XYDataFromPath(name='Temperatura',path=session.Path(name='track', type=POINT_LIST, expression=thePointList),
                                                 includeIntersections=False, shape=UNDEFORMED, labelType=TRUE_DISTANCE, step=0, frame=licznik,  variable=(('NT11', NODAL),))

        Temperature = TemperaturaXYData.data[0]
        TemperatureList.extend([Temperature[1]])

    odb.close
    return TemperatureList







import xalglib

licz=0
def function1(p, fi, param):
    global licz

    tempp=[138.7701721, 85.02330017, 55.33176804, 39.19210434, 30.42494774
]
    lenExp=len(tempp)
    a1=p[0]

    cube(a1)
    sim=dataT()
    sumaa = 0.0
    licz=licz+1
    for i in range (0,lenExp):
        sumaa = sumaa + (sim[i]-tempp[i])





    fi[0] = sumaa	#definicja funkcji celu
    print licz
    print sumaa
    print "alpha: ", p
    print sim
    return


p = [0.25] #definicja poczatkowych wartosci wektora rozwiazan
bndl = [0.25] #ograniczenia dolne
bndu = [1.0] #ograniczenia gorne
epsX = 0.01 #kryterium stopu
maxits = 0 #Maksymalna liczba iteracji, jezeli maxits=0 to liczba iteracji jest nieograniczona
DiffStep = 0.0001 #numeryczny krok rozniczkowania
j=1
state = xalglib.minlmcreatev(j, p, DiffStep)
xalglib.minlmsetbc(state, bndl, bndu)
xalglib.minlmsetcond(state, epsX, maxits)
xalglib.minlmoptimize_v(state, function1)
p, rep = xalglib.minlmresults(state)
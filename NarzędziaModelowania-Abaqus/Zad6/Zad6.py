import xalglib
from abaqus import *
from abaqusConstants import *
from odbAccess import *
from odbSection import *
from sys import argv, exit
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
    mdb.models['Model-1'].setValues(absoluteZero=-273.15, 
        stefanBoltzmann=5.67037E-11)
    s = mdb.models['Model-1'].ConstrainedSketch(name='__profile__', 
        sheetSize=200.0)
    g, v, d, c = s.geometry, s.vertices, s.dimensions, s.constraints
    s.setPrimaryObject(option=STANDALONE)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=105.117, 
        farPlane=272.007, width=542.245, height=201.232, cameraPosition=(
        -105.267, 13.1482, 188.562), cameraTarget=(-105.267, 13.1482, 0))
    s.rectangle(point1=(0.0, 0.0), point2=(100.0, 100.0))
    p = mdb.models['Model-1'].Part(name='Part-1', dimensionality=THREE_D, 
        type=DEFORMABLE_BODY)
    p = mdb.models['Model-1'].parts['Part-1']
    p.BaseSolidExtrude(sketch=s, depth=100.0)
    s.unsetPrimaryObject()
    p = mdb.models['Model-1'].parts['Part-1']
    session.viewports['Viewport: 1'].setValues(displayedObject=p)
    del mdb.models['Model-1'].sketches['__profile__']
    session.viewports['Viewport: 1'].partDisplay.setValues(sectionAssignments=ON, 
        engineeringFeatures=ON)
    session.viewports['Viewport: 1'].partDisplay.geometryOptions.setValues(
        referenceRepresentation=OFF)
    mdb.models['Model-1'].Material(name='Material-1')
    mdb.models['Model-1'].materials['Material-1'].Density(table=((7.9e-09, ), ))
    mdb.models['Model-1'].materials['Material-1'].SpecificHeat(table=((500000000.0, 
        ), ))
    mdb.models['Model-1'].materials['Material-1'].Conductivity(table=((50.0, ), ))
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
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(loads=ON, bcs=ON, 
        predefinedFields=ON, connectors=ON)
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
        predefinedFields=OFF, connectors=OFF, adaptiveMeshConstraints=ON)
    mdb.models['Model-1'].HeatTransferStep(name='Step-1', previous='Initial', 
        timePeriod=500.0, initialInc=5.0, minInc=1.0, maxInc=20.0, deltmx=100.0)
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(interactions=ON, 
        constraints=ON, connectors=ON, engineeringFeatures=ON, 
        adaptiveMeshConstraints=OFF)
    session.viewports['Viewport: 1'].view.setValues(nearPlane=234.98, 
        farPlane=495.837, width=319.374, height=110.268, cameraPosition=(
        249.663, 29.6859, -255.404), cameraUpVector=(-0.10321, 0.954362, 
        0.280252))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=227.196, 
        farPlane=502.16, width=308.795, height=106.615, cameraPosition=(
        -162.448, -112.196, -198.141), cameraUpVector=(0.0720573, 0.97852, 
        -0.193148), cameraTarget=(52.6004, 45.9772, 52.0281))
    mdb.models['Model-1'].FilmConditionProp(name='IntProp-1', 
        temperatureDependency=OFF, dependencies=0, property=((alpha, ), ))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=233.105, 
        farPlane=499.98, width=316.826, height=109.388, cameraPosition=(
        301.722, -64.6529, -190.554), cameraUpVector=(-0.906126, -0.0245183, 
        -0.422296), cameraTarget=(51.1035, 45.8239, 52.0036))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=232.318, 
        farPlane=509.019, width=315.756, height=109.019, cameraPosition=(
        249.318, -163.502, 278.231), cameraUpVector=(-0.164952, -0.493461, 
        -0.853983), cameraTarget=(51.005, 45.6381, 52.8845))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=231.56, 
        farPlane=506.267, width=314.726, height=108.663, cameraPosition=(
        272.427, 216.854, 292.457), cameraUpVector=(0.197694, -0.9802, 
        -0.0112112), cameraTarget=(51.3052, 50.5792, 53.0693))
    a = mdb.models['Model-1'].rootAssembly
    s1 = a.instances['Part-1-1'].faces
    side1Faces1 = s1.getSequenceFromMask(mask=('[#3f ]', ), )
    region=a.Surface(side1Faces=side1Faces1, name='Surf-1')
    mdb.models['Model-1'].FilmCondition(name='Int-1', createStepName='Step-1', 
        surface=region, definition=PROPERTY_REF, 
        interactionProperty='IntProp-1', sinkTemperature=20.0, 
        sinkAmplitude='', sinkDistributionType=UNIFORM, sinkFieldName='')
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
    p1 = mdb.models['Model-1'].parts['Part-1']
    session.viewports['Viewport: 1'].setValues(displayedObject=p1)
    p = mdb.models['Model-1'].parts['Part-1']
    p.seedPart(size=12.0, deviationFactor=0.1, minSizeFactor=0.1)
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
    mdb.Job(name='Job-1', model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
    mdb.jobs['wyn'].writeInput(consistencyChecking=OFF)
    mdb.jobs['wyn'].submit()
    mdb.jobs['wyn'].waitForCompletion()
    
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
	
	node=365		#node number
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

liczba=0
def function1(p, fi, param):
    global liczba

    Teksp=[138.7701721, 85.02330017, 55.33176804, 39.19210434, 30.42494774]
    leng=len(Teksp)
    a1=p[0]

    cube(a1)
    Tobl=dataT()
    S = 0.0
    liczba=liczba+1
    for i in range (0,leng):
        S = S + (Tobl[i]-Teksp[i])





    fi[0] = S	#definicja funkcji celu
    print liczba
    print S
    print "alpha: ", p
    print Tobl
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
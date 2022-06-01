import xalglib
from abaqus import *
from abaqusConstants import *
from odbAccess import *
from odbSection import *
from sys import argv, exit
import __main__

from abaqus import *
from abaqusConstants import *
import __main__

def Macro1(alpha1,alpha2,alpha3,alpha4):
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
        temperatureDependency=ON, dependencies=0, property=((alpha1/1000, 20.0), (
        alpha2/1000, 190.0), (alpha3/1000, 340.0), (alpha4/1000, 650.0)))
    session.viewports['Viewport: 1'].assemblyDisplay.setValues(step='Step-1')
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
    p = mdb.models['Model-1'].parts['coil']
    c = p.cells
    pickedCells = c.getSequenceFromMask(mask=('[#1 ]', ), )
    v1, e, d1 = p.vertices, p.edges, p.datums
    p.PartitionCellByPlaneThreePoints(cells=pickedCells, point1=p.InterestingPoint(
        edge=e[1], rule=CENTER), point2=p.InterestingPoint(edge=e[1], 
        rule=MIDDLE), point3=p.InterestingPoint(edge=e[0], rule=MIDDLE))
    session.viewports['Viewport: 1'].view.setValues(nearPlane=4641.86, 
        farPlane=8206.74, width=4750.31, height=2105.69, viewOffsetX=336.531, 
        viewOffsetY=23.7984)
    p = mdb.models['Model-1'].parts['coil']
    e = p.edges
    pickedEdges = e.getSequenceFromMask(mask=('[#10 ]', ), )
    p.seedEdgeByNumber(edges=pickedEdges, number=5, constraint=FINER)
    p = mdb.models['Model-1'].parts['coil']
    p.seedPart(size=160.0, deviationFactor=0.1, minSizeFactor=0.1)
    p = mdb.models['Model-1'].parts['coil']
    p.generateMesh()
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
    mdb.Job(name='Job-1', model='Model-1', description='', type=ANALYSIS, 
        atTime=None, waitMinutes=0, waitHours=0, queue=None, memory=90, 
        memoryUnits=PERCENTAGE, getMemoryFromAnalysis=True, 
        explicitPrecision=SINGLE, nodalOutputPrecision=SINGLE, echoPrint=OFF, 
        modelPrint=OFF, contactPrint=OFF, historyPrint=OFF, userSubroutine='', 
        scratch='', resultsFormat=ODB)
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
    session.viewports['Viewport: 1'].odbDisplay.setFrame(step=0, frame=37 )
    session.viewports['Viewport: 1'].odbDisplay.setFrame(step=0, frame=37 )
    mdb.jobs['Job-1'].writeInput(consistencyChecking=OFF)
    mdb.jobs['Job-1'].submit()
    mdb.jobs['Job-1'].waitForCompletion()

    
    


def	dataT ():
	odbName='C:/temp/Job-1.odb'
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
	
	node=883		#node number
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

liczba=0
def function1(p, fi, param):
    global liczba

    Teksp=[362.88, 201.5, 124.4, 92.3, 63, 42.17]
    
    leng=len(Teksp)

    Macro1(p[0],p[1],p[2],p[3])
    Tobl=dataT()
    S = 0.0
    liczba=liczba+1
    for i in range (0,leng):
        S = S + (Tobl[i]-Teksp[i])**2





    fi[0] = S	#definicja funkcji celu
    print liczba
    print S
    print "alpha: ", p
    print Tobl
    return


p = [4, 1, 0.05, 0.05]
bndl= [0.05, 0.05, 0.05, 0.05]
bndu= [6, 6, 6, 6]
epsX= 0.01
maxits= 0
DiffStep= 0.0001

j=1
state = xalglib.minlmcreatev(j, p, DiffStep)
xalglib.minlmsetbc(state, bndl, bndu)
xalglib.minlmsetcond(state, epsX, maxits)
xalglib.minlmoptimize_v(state, function1)
p, rep = xalglib.minlmresults(state)

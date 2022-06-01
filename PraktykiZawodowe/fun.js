function toGeo(){
			PokazTekst();
			var e = document.getElementById("opt1");
			var strUser = e.options[e.selectedIndex].value;
			var kWh=dod1/0.65;
				document.getElementById("orient4").innerHTML= net.toFixed(2)+ " kWh";
			document.getElementById("wyn1").innerHTML= dod1 + " złotych*";
			document.getElementById("wyn2").innerHTML= dod1*25 + " złotych*";
			document.getElementById("wyn3").innerHTML= kWh + " kWh";
			document.getElementById("wyn4").innerHTML= wyn + " kWp";
			document.getElementById("orient2").innerHTML= auto + " %";
			$('html, body').animate({scrollTop:830}, '10');
		}
		function PokazTekst() {
			var P1 = document.getElementById('container');
			var P2 = document.getElementById('orient');
			var P3 = document.getElementById('panele');
			var P4 = document.getElementById('koniec');
				P1.style.display = 'block';
				P2.style.display = 'block';
				P3.style.display = 'block';
				P4.style.display = 'block';
		}
		function wpisz(){
			var podst= (-1)*(wyn*4000);
			document.getElementById("r1").innerHTML= podst;
			document.getElementById("r2").innerHTML= Number(podst)+Number(dod1);
			document.getElementById("r3").innerHTML= Number(podst)+2*Number(dod1);
			document.getElementById("r4").innerHTML= Number(podst)+3*Number(dod1);
			document.getElementById("r5").innerHTML= Number(podst)+4*Number(dod1);
			document.getElementById("r6").innerHTML= Number(podst)+5*Number(dod1);
			document.getElementById("r7").innerHTML= Number(podst)+6*Number(dod1);
			document.getElementById("r8").innerHTML= Number(podst)+7*Number(dod1);
			document.getElementById("r9").innerHTML= Number(podst)+8*Number(dod1);
			document.getElementById("r10").innerHTML= Number(podst)+9*Number(dod1);
			document.getElementById("r11").innerHTML= Number(podst)+10*Number(dod1);
			document.getElementById("r12").innerHTML= Number(podst)+11*Number(dod1);
			
		}
		function gra() { 
			if(wyn==0){
				document.getElementById("diag").innerHTML="Ustaw wartości oraz oblicz zużycie energii";
			} else{
			   var data = {
				  table: 'datatable'
			   };
			   var chart = {
				  type: 'column'
			   };
			   var title = {
				  text: 'Zwrot inwestycji'   
			   };      
			   var yAxis = {
				  allowDecimals: false,
				  title: {
					 text: 'Złotych'
				  }
			   };
			   var xAxis = {
				  allowDecimals: false,
				  title: {
					   text: 'Lata'
				  }
			   };
			   var tooltip = {
				  formatter: function () {
					 return '<b>' + this.series.name + '</b> <br/>' +
						this.point.y + ' ' + this.point.name.toLowerCase();
				  }
			   };
			   var credits = {
				  enabled: false
			   };  
				  
			   var json = {};   
			   json.chart = chart; 
			   json.title = title; 
			   json.data = data;
			   json.yAxis = yAxis;
			   json.xAxis = xAxis;
			   json.credits = credits;  
			   json.tooltip = tooltip;  
			   wpisz();
			   $('#diag').highcharts(json);
			   $('html, body').animate({scrollTop:1830}, '10');
			}
		}
		
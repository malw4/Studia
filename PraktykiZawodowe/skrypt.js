var wyn=0;
var dod1;
		function zapotrzebowanie(){
			PokazTekst();
			var e = document.getElementById("opt1");
			var strUser = e.options[e.selectedIndex].value;
			var f = document.getElementById("opt3");
			var auto = f.options[f.selectedIndex].value;
			dod1=document.getElementById("pole1").value;
			dod1=dod1*strUser;
			var kWh=dod1/0.65;
			var kW=kWh/(24*37.88);
			wyn=kW.toFixed(2);
			kWh=kWh.toFixed(2);
			var orient = wyn*4000;
			var net=0;
			if(wyn<10){
				net=kW*0.8;
				document.getElementById("orient4").innerHTML= net.toFixed(2)+ " kWh";
			} else if(wyn>10&&wyn<50){
				net=kW*0.7;
				document.getElementById("orient4").innerHTML= net.toFixed(2)+ " kWh";
			} else{
				document.getElementById("orient4").innerHTML= "Zapytaj swojego sprzedawcę energii";
			}
			document.getElementById("wyn1").innerHTML= dod1 + " złotych*";
			document.getElementById("wyn2").innerHTML= dod1*25 + " złotych*";
			document.getElementById("wyn3").innerHTML= kWh + " kWh";
			document.getElementById("wyn4").innerHTML= wyn + " kWp";
			document.getElementById("orient2").innerHTML= auto + " %";
			return wyn;
		}
		function modules(){
			zapotrzebowanie();
			var liczba1;
			var liczb2; 
			var liczb3;
			var pole1; 
			var pole2;
			var pole3;
			liczba1=(wyn*1000)/340;
			liczba2=(wyn*1000)/365;
			liczba3=(wyn*1000)/400;
			pole1=liczba1*1.687368;
			pole2=liczba2*1.84972;
			pole3=liczba3*2.012016;
			document.getElementById("pan11").innerHTML= Math.ceil(liczba1);
			document.getElementById("pan21").innerHTML= Math.ceil(liczba2);
			document.getElementById("pan31").innerHTML= Math.ceil(liczba3);
			document.getElementById("pan12").innerHTML= pole1.toFixed(2)+" m²";
			document.getElementById("pan22").innerHTML= pole2.toFixed(2)+" m²";
			document.getElementById("pan32").innerHTML= pole3.toFixed(2)+" m²";
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
			document.getElementById("r13").innerHTML= Number(podst)+12*Number(dod1);
			document.getElementById("r14").innerHTML= Number(podst)+13*Number(dod1);
			document.getElementById("r15").innerHTML= Number(podst)+14*Number(dod1);
			document.getElementById("r16").innerHTML= Number(podst)+15*Number(dod1);
			document.getElementById("r17").innerHTML= Number(podst)+16*Number(dod1);
			document.getElementById("r18").innerHTML= Number(podst)+17*Number(dod1);
			document.getElementById("r19").innerHTML= Number(podst)+18*Number(dod1);
			document.getElementById("r20").innerHTML= Number(podst)+19*Number(dod1);
			document.getElementById("r21").innerHTML= Number(podst)+20*Number(dod1);
			document.getElementById("r22").innerHTML= Number(podst)+21*Number(dod1);
			document.getElementById("r23").innerHTML= Number(podst)+22*Number(dod1);
			document.getElementById("r24").innerHTML= Number(podst)+23*Number(dod1);
			document.getElementById("r25").innerHTML= Number(podst)+24*Number(dod1);
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
		
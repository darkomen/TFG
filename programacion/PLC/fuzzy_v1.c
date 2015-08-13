(*Vamos almacenando el diámetro medido e incrementamos el numero de muestras tomadas.*)

dim_acumulado:=dim_acumulado+dim;
n_actual:=n_actual+1;

(*Si hemos tomado el numero deseado de muetras empiezamos el control*)
IF n_actual >= n THEN
	(*Calculamos la media*)
	dim_media:=(dim_acumulado/n);
	(*Ajustamos la velocidad*)

	(*Si estamos por debajo del rango, disminuimos la velocidad*)
	IF (dim_media <= (1.60) ) THEN
		caso:=0;
		v:=v-d_v*5;
	ELSIF (dim_media > (1.60) AND dim_media < (1.70) ) AND (dim_media_ant<dim_media)THEN
		caso:=1;
		v:=v+d_v*2.5;
	ELSIF (dim_media > (1.60) AND dim_media < (1.70) ) AND (dim_media_ant>dim_media)THEN
		caso:=2;
		v:=v-d_v*2.5;
	ELSIF (dim_media >= (1.70)) AND (dim_media <= (1.75) ) AND (dim_media_ant<dim_media)THEN
		caso:=3;
		(*12/08/2015 con esta velocidad es una buena aproximació
		v:=v+d_v*1;*)
		v:=v+d_v*2;
	ELSIF (dim_media >= (1.70)) AND (dim_media <= (1.75) ) AND (dim_media_ant>dim_media)THEN
		caso:=4;
		(*12/08/2015 con esta velocidad es una buena aproximació*)
		v:=v-d_v*1;
		(*v:=v-d_v*2;*)
	ELSIF (dim_media > (1.75)) AND (dim_media <= (1.80) ) AND (dim_media_ant<dim_media)THEN
		caso:=5;
		(*
		11/8/2015 con esta velocidad es una buena aproximación
		v:=v+d_v*1;*)
		v:=v+d_v*2;
	ELSIF (dim_media > (1.75)) AND (dim_media <= (1.80) ) AND (dim_media_ant>dim_media)THEN
		caso:=6;
		(*12/08/2015 con esta velocidad es una buena aproximació*)
		v:=v-d_v*1;
		(*v:=v-d_v*2;*)
	ELSIF (dim_media > (1.80) AND dim_media < (1.90))  AND (dim_media_ant<dim_media)THEN
		caso:=7;
		v:=v+d_v*2.5;
	ELSIF (dim_media > (1.80) AND dim_media < (1.90))   AND (dim_media_ant>dim_media)THEN
		caso:=8;
		v:=v-d_v*2.5;
	ELSIF (dim_media >= (1.90))  THEN
		caso:=9;
		v:=v+d_v*5;
	END_IF;

~~
(*

 	CASE caso OF
		0:
			v:=v-d_v*5;
		1,7:
			v:=v-+d_v*2;
		2,8:
			v:=v-d_v*2;
		3,5:
			v:=v-+d_v*1;
		4,6:
			v:=v-d_v*1;
		9:
			v:=v-+d_v*5;

	END_CASE

*)
	(*Hacemos que lavariable de salida no pase los límites marcados.*)
	IF (v <= v_min )THEN
		 v:=v_min;
	END_IF;

	IF (v >= v_max) THEN
		 v:=v_max;
	END_IF;


	(*Reseteamos contadores para la siguiente iteracción*)
	n_actual:=0;
	dim_acumulado:=0;
	dim_media_ant:=dim_media;

END_IF;
	 v_:=v;  (*Volcamos la V calculada a la salida*)
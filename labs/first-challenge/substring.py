def subString(palabra):
    cadenaF=[]
    cuCadena=[]
    inicial=0
    for i in range(0,len(palabra)):
        for j in range(i,len(palabra)):
            if(palabra[j] in cuCadena):
                if(len(cuCadena)>len(cadenaF)):
                    cadenaF=cuCadena
                    cuCadena=[]
                else:
                    cuCadena=[]        
            else:
                cuCadena.append(palabra[j])
    print(cadenaF)
    print(len(cadenaF))
    return(len(cadenaF))
                    
subString("aquivalacadena")

import numpy as np

# Dados de entrada
#Corrente
# x,y,z,p,l = float(input("insira os 5 valores da corrente separados por uma virgula\n"))
# i = np.array([x, y, z, p, l])
# # i = np.array([0.25, 0.75, 1.25, 1.5, 2])
# #Voltagem
# x,y,z,p,l = float((input("insira os 5 valores da voltagem separados os por uma virgula\n")).split(","))
# # v = np.array([-0.45, -0.60, 0.70, 1.88, 6])
# v = np.array([x, y, z, p, l])


def lagrangeInterpolacao(corrente, arrayCorrente, arrayVoltagem):
    n = len(arrayCorrente)
    result = 0
    for i in range(n):
        term = arrayVoltagem[i]
        for j in range(n):
            if i != j:
                term *= (corrente - arrayCorrente[j]) / (arrayCorrente[i] - arrayCorrente[j])
                print(f"Iteração ({i},{j}): term = {term}")
        result += term
        # print(f"Iteração {i}: resultado = {result}")
    return result


# Interpolação polinomial de segundo grau (Newton)
def diferencaDivisao(corrente, x_values, y_values):
    n = len(x_values)
    f = np.zeros((n, n))
    f[:,0] = y_values
    for j in range(1, n):
        for i in range(n-j):
            f[i][j] = (f[i+1][j-1] - f[i][j-1]) / (x_values[i+j] - x_values[i])
            print(f"Iteração ({i},{j}): corrente[{i}] = {corrente[i]}")
    return f

def diferencaDivisao(x, x_values, y_values):
    n = len(x_values)
    f = np.zeros((n, n))
    f[:,0] = y_values
    for j in range(1, n):
        for i in range(n-j):
            f[i][j] = (f[i+1][j-1] - f[i][j-1]) / (x_values[i+j] - x_values[i])
    return f
# Interpolação polinomial de segundo grau (Newton)
def newton_2(corrente, x_values, y_values):
    n = len(x_values)
    f = diferencaDivisao(corrente, x_values, y_values)
    result = f[0][0]
    for i in range(1, n):
        term = f[0][i]
        for j in range(i):
            term *= corrente - x_values[j]
            #exibindo o valor term de cada interação
            
        result += term
        #exibindo o resultado da iteração
        
    return result

# Interpolação polinomial de terceiro grau (Newton)
def newton_3(corrente, x_values, y_values):
    n = len(x_values)
    f = diferencaDivisao(corrente, x_values, y_values)
    result = f[0][0]
    for i in range(1, n):
        term = f[0][i]
        for j in range(i):
            term *= corrente - x_values[j]
        result += term
    return result

# Interpolação polinomial de quarto grau (Newton)
def newton_4(corrente, x_values, y_values):
    n = len(x_values)
    f = diferencaDivisao(corrente, x_values, y_values)
    result = f[0][0]
    for i in range(1, n):
        term = f[0][i]
        for j in range(i):
            term *= corrente - x_values[j]
        result += term
    return result


programa = 1
while programa:
    # x,y,z,p,l = float(input("insira os 5 valores da corrente separados por uma virgula\n"))
    x,y,z,p,l = map(float,input("insira o vetor correspondente a corrente, separado por virgula\n").split(","))
    i = np.array([x, y, z, p, l])
    # i = np.array([0.25,0.75,1.25,1.5,2])
    #Voltagem
    #
    # v = np.array([-0.45,-0.60,0.70,1.88,6])
    x,y,z,p,l = map(float,input("insira o vetor correspondente a tensão, separado por virgula\n").split(","))
    v = np.array([x, y, z, p, l])
    print(i[0:3])
    print(i[0:4])
    print(i[0:5])

    # Estimativa da queda de voltagem para i = 1,15
    corrente = float(input("Insira qual o valor da correne i para se realizar a estimativa:\n"))
    # corrente = 1.15
    newtonEstimativa2 = newton_2(corrente, i, v)
    newtonEstimativa3 = newton_3(corrente, i, v)
    newtonEstimativa4 = newton_4(corrente, i, v)

    lagrangeEstimativa2 = lagrangeInterpolacao(corrente, i[:3], v[:3])
    lagrangeEstimativa3 = lagrangeInterpolacao(corrente, i[:4], v[:4])
    lagrangeEstimativa4 = lagrangeInterpolacao(corrente, i, v)

    print("Interpolação polinomial de segundo grau (Lagrange): ", lagrangeEstimativa2)
    print("Estimativa de terceiro grau (Lagrange): ", lagrangeEstimativa3)
    print("Estimativa de quarto grau (Lagrange): ", lagrangeEstimativa4)

    print("Interpolação polinomial de segundo grau (Newton): ", newtonEstimativa2)
    print("Interpolação polinomial de terceiro grau (Newton): ", newtonEstimativa3)
    print("Interpolação polinomial de quarto grau (Newton): ", newtonEstimativa4)
    programa = int(input("Digite 0 para finalizar o programa, digite 1 para continuar\n"))


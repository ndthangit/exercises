from ortools.sat.python import cp_model


def create_data_model():
    data = {}
    data['num_people'] = int(input())
    data['people'] = {}
    mapping = {'O': 0, 'A': 1, 'B': 2, 'AB': 3}
    for _ in range(data['num_people']):
        parts = input().split()
        idx = int(parts[0])
        bt = int(mapping[parts[1]])
        f = int(parts[2])
        m = int(parts[3])
        data['people'][idx] = {"blood": bt, "parent1": f, "parent2": m}

    return data

def main():
    data =create_data_model()
    # print(data)

    # All valid inheritance rules
    inheritance = {
        (0, 0): {0},
        (0, 1): {0, 1},
        (0, 2): {0, 2},
        (0, 3): {1, 2},
        (1, 0): {0, 1},
        (1, 1): {0, 1},
        (1, 2): {0, 1, 2, 3},
        (1, 3): {1, 2, 3},
        (2, 0): {0, 2},
        (2, 1): {0, 1, 2, 3},
        (2, 2): {0, 2},
        (2, 3): {1, 2, 3},
        (3, 0): {1, 2},
        (3, 1): {1, 2, 3},
        (3, 2): {1, 2, 3},
        (3, 3): {1, 2, 3},
    }
    model = cp_model.CpModel()
    # Variables
    blood = [model.NewIntVar(0, 3, f"blood_{i}") for i in range(data['num_people'])]
    change = [model.NewBoolVar(f"change_{i}") for i in range(data['num_people'])]

    for i in range(data['num_people']):
        # Allow change only if changed from original
        model.Add(blood[i] != data['people'][i]['blood']).OnlyEnforceIf(change[i])
        model.Add(blood[i] == data['people'][i]['blood']).OnlyEnforceIf(change[i].Not())

        if data['people'][i]['parent1'] != -1 and data['people'][i]['parent2'] != -1:
            # Create 16 boolean conditions for parent combinations
            # valid_combinations = []
            # for f_blood in range(4):
            #     for m_blood in range(4):
            #         possible = inheritance.get((f_blood, m_blood), set())
            #         if data['people'][i]['blood'] in possible:
            #             valid_combinations.append((f_blood, m_blood))

            # Build allowed combinations using tables
            tuples = []
            for (f_b, m_b), child_options in inheritance.items():
                for c_b in child_options:
                    tuples.append([f_b, m_b, c_b])

            # Add table constraint
            model.AddAllowedAssignments(
                [blood[data['people'][i]['parent1']], blood[data['people'][i]['parent2']], blood[i]],
                tuples).OnlyEnforceIf(
                change[i].Not())

    # Objective: minimize number of changes
    model.Minimize(sum(change))

    # Solve
    solver = cp_model.CpSolver()
    status = solver.Solve(model)

    # Output
    if status in [cp_model.OPTIMAL, cp_model.FEASIBLE]:
        print(int(solver.ObjectiveValue()))
        for i in range(data['num_people']):
            print(f"{i}: {solver.Value(blood[i])} {solver.Value(change[i])} {data['people'][i]['blood']}")
    else:
        print("No solution found.")

if __name__ == "__main__":
    main()
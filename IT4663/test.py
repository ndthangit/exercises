from ortools.constraint_solver import routing_enums_pb2
from ortools.constraint_solver import pywrapcp
import math


def distance(x1, y1, x2, y2):
    return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)


def solve_pvrptw():
    # Parse input data
    input_data = """6 2 48 4
500 200
500 200
500 200
500 200
  1  -29.730   64.136  2 12 1 4 1 2 4 8 399 525
  2  -30.664    5.463  7  8 1 4 1 2 4 8 121 299
  3   51.642    5.469 21 16 1 4 1 2 4 8 389 483
  4  -13.171   69.336 24  5 1 4 1 2 4 8 204 304
  5  -67.413   68.323  1 12 1 4 1 2 4 8 317 458
  6   48.907    6.274 17  5 1 4 1 2 4 8 160 257
  7    5.243   22.260  6 13 1 4 1 2 4 8 170 287
  8  -65.002   77.234  5 20 1 4 1 2 4 8 215 321
  9   -4.175   -1.569  7 13 1 4 1 2 4 8  80 233
 10   23.029   11.639  1 18 1 4 1 2 4 8  90 206
 11   25.482    6.287  4  7 1 4 1 2 4 8 397 525
 12  -42.615  -26.392 10  6 1 4 1 2 4 8 271 420
 13  -76.672   99.341  2  9 1 4 1 2 4 8 108 266
 14  -20.673   57.892 16  9 1 4 1 2 4 8 340 462
 15  -52.039    6.567 23  4 1 4 1 2 4 8 226 377
 16  -41.376   50.824 18 25 1 4 1 2 4 8 446 604
 17  -91.943   27.588  3  5 1 4 1 2 4 8 444 566
 18  -65.118   30.212 15 17 1 4 1 2 4 8 434 557
 19   18.597   96.716 13  3 1 4 1 2 4 8 319 460
 20  -40.942   83.209 10 16 1 4 1 2 4 8 192 312
 21  -37.756  -33.325  4 25 1 4 1 2 4 8 414 572
 22   23.767   29.083 23 21 1 4 1 2 4 8 371 462
 23  -43.030   20.453 20 14 1 4 1 2 4 8 378 472
 24  -35.297  -24.896 10 19 1 4 1 2 4 8 308 477
 25  -54.755   14.368  4 14 1 4 1 2 4 8 329 444
 26  -49.329   33.374  2  6 1 4 1 2 4 8 269 377
 27   57.404   23.822 23 16 1 4 1 2 4 8 398 494
 28  -22.754   55.408  6  9 1 4 1 2 4 8 257 416
 29  -56.622   73.340  8 20 1 4 1 2 4 8 198 294
 30  -38.562   -3.705 10 13 1 4 1 2 4 8 375 467
 31  -16.779   19.537  7 10 1 4 1 2 4 8 200 338
 32  -11.560   11.615  1 16 1 4 1 2 4 8 456 632
 33  -46.545   97.974 21 19 1 4 1 2 4 8  72 179
 34   16.229    9.320  6 22 1 4 1 2 4 8 182 282
 35    1.294    7.349  4 14 1 4 1 2 4 8 159 306
 36  -26.404   29.529 13 10 1 4 1 2 4 8 321 500
 37    4.352   14.685  9 11 1 4 1 2 4 8 322 430
 38  -50.665  -23.126 22 15 1 4 1 2 4 8 443 564
 39  -22.833   -9.814 22 13 1 4 1 2 4 8 207 348
 40  -71.100  -18.616 18 15 1 4 1 2 4 8 457 588
 41   -7.849   32.074 10  8 1 4 1 2 4 8 203 382
 42   11.877  -24.933 25 22 1 4 1 2 4 8  75 167
 43  -18.927  -23.730 23 24 1 4 1 2 4 8 459 598
 44  -11.920   11.755  4  3 1 4 1 2 4 8 174 332
 45   29.840   11.633  9 25 1 4 1 2 4 8 130 225
 46   12.268  -55.811 17 19 1 4 1 2 4 8 169 283
 47  -37.933  -21.613 10 21 1 4 1 2 4 8 115 232
 48   42.883   -2.966 17 10 1 4 1 2 4 8 414 531
 49    4.163   13.559  0  0 0 0  0 1000
 50   21.387   17.105  0  0 0 0  0 1000
 51  -36.118   49.097  0  0 0 0  0 1000
 52  -31.201    0.235  0  0 0 0  0 1000"""

    lines = input_data.split('\n')

    # Parse first line
    first_line = lines[0].split()
    problem_type = int(first_line[0])
    num_vehicles = int(first_line[1])
    num_customers = int(first_line[2])
    num_days = int(first_line[3])

    # Parse vehicle capacities for each day
    vehicle_capacities = []
    max_durations = []
    for i in range(1, num_days + 1):
        parts = lines[i].split()
        max_durations.append(int(parts[0]))
        vehicle_capacities.append(int(parts[1]))

    # Parse customer data
    customers = []
    depots = []
    for line in lines[num_days + 1:]:
        parts = line.split()
        if len(parts) < 10:
            continue
        customer_id = int(parts[0])
        x = float(parts[1])
        y = float(parts[2])
        service_duration = int(parts[3])
        demand = int(parts[4])
        frequency = int(parts[5])
        num_combinations = int(parts[6])
        combinations = list(map(int, parts[7:7 + num_combinations]))
        time_window_start = int(parts[7 + num_combinations])
        time_window_end = int(parts[8 + num_combinations])

        if demand == 0 and service_duration == 0:
            depots.append((x, y))
        else:
            customers.append({
                'id': customer_id,
                'x': x,
                'y': y,
                'service_duration': service_duration,
                'demand': demand,
                'frequency': frequency,
                'combinations': combinations,
                'time_window': (time_window_start, time_window_end)
            })

    # Since this is a complex problem, we'll solve it day by day
    # For each day, we'll select customers that should be visited on that day
    # and solve a standard VRPTW for each day

    # Create a distance matrix for all locations (customers + depots)
    all_locations = depots + [(c['x'], c['y']) for c in customers]
    num_locations = len(all_locations)
    distance_matrix = [[0] * num_locations for _ in range(num_locations)]
    for i in range(num_locations):
        for j in range(num_locations):
            if i != j:
                distance_matrix[i][j] = distance(all_locations[i][0], all_locations[i][1],
                                                 all_locations[j][0], all_locations[j][1])

    # For each day, determine which customers need to be visited
    for day in range(1, num_days + 1):
        day_customers = []
        for customer in customers:
            for comb in customer['combinations']:
                if comb & (1 << (day - 1)):
                    day_customers.append(customer)
                    break

        if not day_customers:
            print(f"Day {day}: No customers to visit")
            continue

        # Create data model for this day's VRPTW
        data = {}
        data['distance_matrix'] = distance_matrix
        data['num_vehicles'] = num_vehicles
        data['depot'] = 0  # Using the first depot as starting point

        # For this day's customers, create demands and time windows
        demands = [0] * num_locations
        time_windows = [(0, 2000)] * num_locations  # Default large window for depots

        customer_indices = []
        for customer in day_customers:
            idx = all_locations.index((customer['x'], customer['y']))
            demands[idx] = customer['demand']
            time_windows[idx] = customer['time_window']
            customer_indices.append(idx)

        data['demands'] = demands
        data['vehicle_capacities'] = [vehicle_capacities[day - 1]] * num_vehicles
        data['time_windows'] = time_windows
        data['service_times'] = [0] * num_locations
        for customer in day_customers:
            idx = all_locations.index((customer['x'], customer['y']))
            data['service_times'][idx] = customer['service_duration']

        # Solve VRPTW for this day
        manager = pywrapcp.RoutingIndexManager(
            len(data['distance_matrix']), data['num_vehicles'], data['depot'])

        routing = pywrapcp.RoutingModel(manager)

        # Add distance constraint
        def distance_callback(from_index, to_index):
            from_node = manager.IndexToNode(from_index)
            to_node = manager.IndexToNode(to_index)
            return data['distance_matrix'][from_node][to_node]

        transit_callback_index = routing.RegisterTransitCallback(distance_callback)
        routing.SetArcCostEvaluatorOfAllVehicles(transit_callback_index)

        # Add capacity constraint
        def demand_callback(from_index):
            from_node = manager.IndexToNode(from_index)
            return data['demands'][from_node]

        demand_callback_index = routing.RegisterUnaryTransitCallback(demand_callback)
        routing.AddDimensionWithVehicleCapacity(
            demand_callback_index,
            0,  # null capacity slack
            data['vehicle_capacities'],  # vehicle maximum capacities
            True,  # start cumul to zero
            'Capacity')

        # Add time window constraint
        def time_callback(from_index, to_index):
            from_node = manager.IndexToNode(from_index)
            to_node = manager.IndexToNode(to_index)
            travel_time = data['distance_matrix'][from_node][to_node]
            service_time = data['service_times'][from_node]
            return travel_time + service_time

        time_callback_index = routing.RegisterTransitCallback(time_callback)

        routing.AddDimension(
            time_callback_index,
            2000,  # allow waiting time
            max_durations[day - 1],  # maximum time per vehicle
            False,  # Don't force start cumul to zero
            'Time')

        time_dimension = routing.GetDimensionOrDie('Time')

        # Add time window constraints for each location except depot
        for location_idx in customer_indices:
            index = manager.NodeToIndex(location_idx)
            time_dimension.CumulVar(index).SetRange(
                data['time_windows'][location_idx][0],
                data['time_windows'][location_idx][1])

        # Add time window constraints for vehicle start nodes
        for vehicle_id in range(data['num_vehicles']):
            index = routing.Start(vehicle_id)
            time_dimension.CumulVar(index).SetRange(
                data['time_windows'][data['depot']][0],
                data['time_windows'][data['depot']][1])

        # Setting first solution heuristic
        search_parameters = pywrapcp.DefaultRoutingSearchParameters()
        search_parameters.first_solution_strategy = (
            routing_enums_pb2.FirstSolutionStrategy.PATH_CHEAPEST_ARC)
        search_parameters.time_limit.seconds = 30

        # Solve the problem
        solution = routing.SolveWithParameters(search_parameters)

        # Print solution for this day
        print(f"\nDay {day} solution:")
        if solution:
            total_distance = 0
            total_load = 0
            for vehicle_id in range(data['num_vehicles']):
                index = routing.Start(vehicle_id)
                plan_output = f'Route for vehicle {vehicle_id}:\n'
                route_distance = 0
                route_load = 0
                while not routing.IsEnd(index):
                    node_index = manager.IndexToNode(index)
                    route_load += data['demands'][node_index]
                    time_var = time_dimension.CumulVar(index)
                    plan_output += (
                        f'{node_index} '
                        f'Load({route_load}) '
                        f'Time({solution.Min(time_var)}, {solution.Max(time_var)}) -> ')
                    previous_index = index
                    index = solution.Value(routing.NextVar(index))
                    route_distance += routing.GetArcCostForVehicle(
                        previous_index, index, vehicle_id)
                time_var = time_dimension.CumulVar(index)
                plan_output += (
                    f'{manager.IndexToNode(index)} '
                    f'Load({route_load}) '
                    f'Time({solution.Min(time_var)}, {solution.Max(time_var)})\n')
                plan_output += f'Distance of the route: {route_distance}m\n'
                plan_output += f'Load of the route: {route_load}\n'
                print(plan_output)
                total_distance += route_distance
                total_load += route_load
            print(f'Total distance of all routes: {total_distance}m')
            print(f'Total load of all routes: {total_load}')
        else:
            print('No solution found for this day.')


if __name__ == '__main__':
    solve_pvrptw()
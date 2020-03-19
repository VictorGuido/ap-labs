package main
 import (
 "fmt"
 "math"
 "math/rand"
 "os"
 "strconv"
 "time"
//"bufio"
)
 type Point struct{ x,y float64}

// X returns point value
func (p Point) X() float64 { 
	return p.x
}

// Y returns point value
func (p Point) Y() float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	 return math.Hypot((q.x-p.x), (q.y-p.y))
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 { 
	return math.Round(math.Hypot(q.x-p.x, q.y-p.y)*100) / 100
}

func geneRandom()float64{ 
	rand.Seed(time.Now().UnixNano()) 
	return math.Round(((rand.Float64()*200)-100)*100) / 100
}

func doIntersect(p1, q1, p2, q2 Point) bool { 
	o1 := orientation(p1, q1, p2) 
	o2 := orientation(p1, q1, q2) 
	o3 := orientation(p2, q2, p1) 
	o4 := orientation(p2, q2, q1) 
	if (o1 != o2) && (o3 != o4) {
		return true
	}
	if (o1 == 0) && onSegment(p1, p2, q1) { 
		return true
	}
	if (o2 == 0) && onSegment(p1, q2, q1) { 
		return true
	}
	if (o3 == 0) && onSegment(p2, p1, q2) { 
		return true
	}
	if (o4 == 0) && onSegment(p2, q1, q2) { 
		return true
	}
	return false
}

func onSegment(p, q, r Point) bool { 
	if (q.X() <= math.Max(p.X(), r.X())) && (q.X() >= math.Min(p.X(), r.X())) && (q.Y() <= math.Max(q.Y(), r.Y())) && (q.Y() >= math.Min(p.Y(), r.Y())) {
		return true
	}
	return false
}

func orientation(p, q, r Point) int { 
	counter := (q.Y()-p.Y())*(r.X()-q.X()) - (q.X()-p.X())*(r.Y()-q.Y()) 
	if counter == 0 {
		return 0
	}
	if counter > 0 { 
		return 1
	}
	return 2
}

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 { 
	sum := 0.0 
	for i := range path { 
		if i > 0 { 
			sum += path[i-1].Distance(path[i])
		}
	}
	return math.Round(sum*100) / 100
}

func (path Path) intersection() bool{ 
	intersect := false 
	for i := 0; i < len(path)-3; i++ {
		for j := 0; j < i+1; j++ { 
			intersect = doIntersect(path[j], path[j+1], path[len(path)-2], path[len(path)-1])
		}
	}
	return intersect
}

func calcuPer(lines int, path Path){ 
	fmt.Println("- Figure's Perimeter") 
	fmt.Print("- ")
	var perimeter = 0.0 
	var i =0 
	for i< lines{ 
		if i== lines-1{ 
			perimeter = perimeter + path[i].Distance(path[(i+1)%lines]) 
			fmt.Printf(" %.1f =", path[i].Distance(path[(i+1)%lines])) 
			fmt.Printf(" %.1f\n", perimeter) 
	    		return
	    }
	perimeter = perimeter + path[i].Distance(path[(i+1)%lines]) 
	fmt.Printf(" %.1f +", path[i].Distance(path[(i+1)%lines])) 
	i++
	}
} 

func main() {
	/*reader := bufio.NewReader(os.Stdin) 
	fmt.Print("Introduce the egdes: ") 
    	edges, _ := reader.ReadString('\n') 
	var lines int lines,_ = strconv.Atoi(edges)*/ 
    	lines, _ := strconv.Atoi(os.Args[1]) 
	if(lines<3){
        	fmt.Println("\nPlease introduce more than 2 egdes") 
		return
    	}
    	fmt.Printf("\n- Generating a [%d] sides figure", lines) 
	fmt.Println("\n- Figure's vertices") 
	figure := Path{} 
	for i := 0; i < lines; i++ { //we will be calling this for for every point that we want to add to the path
		figure = append(figure, Point{geneRandom(), geneRandom()}) 
		for figure.intersection() {
			figure[i] = Point{geneRandom(), geneRandom()}
		}
		fmt.Printf("- ( %.1f, %.1f)\n", figure[i].X(), figure[i].Y())
	}
	calcuPer(lines, figure)
}

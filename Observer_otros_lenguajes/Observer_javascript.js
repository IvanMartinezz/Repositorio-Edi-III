class Observable {
    constructor() {
        this.observers = [];
    }

    //SUSCRIBE UNA CLASE NOTIFICADORA
    suscribe (c) {
        this.observers.push(c);
    }

    //DESUSCRIBE LA CLASE NOTIFICADORA
    unsubscribe(c){
        this.observers = this.observers.filter(observer => observer instanceof c !== true);
    }

    // LLAMA A TODOS NUESTROS SUSCRIPTORES 
    notify(model){
        this.observers.forEach(observer => {
            observer.notify(model);
        });
    }
}

class NumberExample extends Observable {
    constructor() {
        super();
        this.value = 0;
    }

    increment(){
        this.value++;
    

    //Llama A LOS SUSCRIPTORES 
    this.notify(this);
    }
}

class NumberExampleSpanishConsole {
    notify(model) {
        console.log(`El nuevo numero es ${model.value}`);
    }
}

class NumberExampleEnglishConsole {
    notify(model){
        console.log(`The new number is ${model.value}`);
    }
}

let numberExample = new NumberExample();

//Le suscribimos sus suscriptores y listeners
numberExample.suscribe(new NumberExampleEnglishConsole());
numberExample.suscribe(new NumberExampleSpanishConsole());

numberExample.increment();

numberExample.increment();

numberExample.increment();


<?php
class Articulo implements \SplSubject /*Empezamos importando la interfaz del sujeto*/
{
    protected $storage;
 
    public function __construct(\SplObjectStorage $storage)
    {
        $this->storage = $storage;
    }
 
    public function compra()
    {
        // compra
        $this->notify('comprado');
    }
 
    public function vende()
    {
        // vende
        $this->notify('vendido');
    }
 
    public function attach(\SplObserver $observer)
    {
        $this->storage->attach($observer);
    }
 
    public function detach(\SplObserver $observer)
    {
        $this->storage->detach($observer);
    }
 
    public function notify($event = '')
    {
        foreach ($this->storage as $observer)
            $observer->update($this, $event);
    }
}
 
class Notify implements \SplObserver /*seguimos con lai implementacion del observer*/
{
    public function update(\SplSubject $subject, $event = '')
    {
        if ($event == 'comprado')
            echo 'El artículo se ha comprado' . PHP_EOL;
        else if ($event == 'vendido')
            echo 'El artículo se ha vendido' . PHP_EOL;
    }
}
 
/*Creamos el objeto*/
$articulo = new Articulo(new \SplObjectStorage());
/*vinculamos el artículo al observer*/
$articulo->attach(new Notify()); 
/*imprimiría en pantalla que se ha comprado*/
$articulo->compra();
/*imprimiría que se ha vendido*/
$articulo->vende();

?>
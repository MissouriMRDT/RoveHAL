/////////////////////////////////////////////////////////////////////////////////////////////////////
// MRDT 2019
/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ROVE_RING_BUFF_H
#define ROVE_RING_BUFF_H

/////////////////////////////////////////////////////////////////////////////////
// Todo support for NO_OVERWRITE bool arg flag??
// Todo => void pushToFront( TYPE value );
// Todo => TYPE popToBack( );
// Todo => TYPE peekFromBack(  uint32_t index );
// Todo => bool isFull();
// if( this->isFull() ) { this->tail = (this->tail + 1) % (SIZE-1);} this->cnt++;

#include <stdint.h>
#include <stddef.h>

///////////////////////////////////////////////////////
template< class TYPE, size_t SIZE > class RoveRingBuff
{
  public:
    TYPE     buff[ SIZE ];
    uint32_t head =     0;
    uint32_t tail =     0;
    size_t   cnt  =     0;
    
    TYPE popFromFront();
    TYPE peekFromFront( uint32_t index=0 );
    void pushToBack(       TYPE value   );
    bool isEmpty();
    TYPE average();
};

///////////////////////////////////////////////////////////////////////////////////
template< class TYPE, size_t SIZE > TYPE RoveRingBuff< TYPE, SIZE >::popFromFront()
{ 
  if(  ( this->isEmpty() )
    || ( this->tail > SIZE ) ){
      return ~TYPE(0); }

  else {
      TYPE  pop_byte =  this->buff[ this->tail ];
      this->tail =                ( this->tail + 1 ) % SIZE;
      this->cnt--;
      return pop_byte; }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
template<class TYPE, size_t SIZE> TYPE RoveRingBuff< TYPE, SIZE >::peekFromFront( uint32_t index )
{
  if(  ( this->isEmpty() )
    || ( this->tail > SIZE ) ){
      return ~TYPE(0); } 

  else {
      return this->buff[ this->tail ]; }
}

/////////////////////////////////////////////////////////////////////////////////////////////
template< class TYPE, size_t SIZE > void RoveRingBuff< TYPE, SIZE >::pushToBack( TYPE value )
{
  this->buff[   this->head]     = value;
  this->head = (this->head + 1) % SIZE;
  
  if ( this->cnt <= SIZE ){
    this->cnt++; }

  else {
    this->tail = (this->tail + 1) % SIZE; }
}

//////////////////////////////////////////////////////////////////////////////
template< class TYPE, size_t SIZE > bool RoveRingBuff< TYPE, SIZE >::isEmpty()
{ return ( this->cnt == 0 ); }

//////////////////////////////////////////////////////////////////////////////
template< class TYPE, size_t SIZE > TYPE RoveRingBuff< TYPE, SIZE >::average()
{
  if( this->cnt == 0 ){
    return 0; }

  else {
    uint32_t sum  =0;
    for( int   i  =0; i < this->cnt;  i++ )
    {        sum +=       this->buff[ i ]; }
    return   sum  /       this->cnt; }
}

#endif // ROVE_RING_BUFF_H
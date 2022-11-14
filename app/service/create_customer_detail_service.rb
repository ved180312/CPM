# frozen_string_literal: true

# ud services
class CreateCustomerDetailService
  def initialize(id)
    @id = id
  end

  def call
    @slot = Slot.find(@id)
    raise 'Already Booked' if @slot.customer_detail
  end
end

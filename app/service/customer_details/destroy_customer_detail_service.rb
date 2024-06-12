# frozen_string_literal: true
module CustomerDetails
  class DestroyCustomerDetailService
    def initialize(customer_detail)
      @customer_detail = customer_detail
    end

    def call
      @customer_detail.slot.status = false

      if @customer_detail.destroy
      @customer_detail.slot.save
      return true
      else
      return false
      end
    end
  end
end
